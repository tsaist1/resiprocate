#include <vector>

#include "resiprocate/os/SharedPtr.hxx"
#include "resiprocate/dum/DumFeature.hxx"
#include "resiprocate/dum/DumFeatureChain.hxx"
#include "resiprocate/Message.hxx"

using namespace resip;
using namespace std;

class GuardFeature : public DumFeature
{
   public:
      GuardFeature(DialogUsageManager& dum)
         : DumFeature(dum)
      {}

      virtual ProcessingResult process(Message* msg)
      {
         return DumFeature::FeatureDone;
      }
};

DumFeatureChain::DumFeatureChain(DialogUsageManager& dum,
                                 const FeatureList& features)
   :mFeatures(features)
{
   mFeatures.push_back(SharedPtr<DumFeature>(new GuardFeature(dum)));
   for (FeatureList::size_type i = 0; i < mFeatures.size(); ++i)
   {
      mActiveFeatures.push_back(true);
   }
}

DumFeatureChain::ProcessingResult DumFeatureChain::process(Message* msg)
{
   FeatureList::iterator feat = mFeatures.begin();
   vector<bool>::iterator active = mActiveFeatures.begin();
   bool stop = false;

   DumFeature::ProcessingResult pres = DumFeature::FeatureDone;
   do
   {
      if (*active)
      {
         pres = (*feat)->process(msg);

         switch(pres)
         {
            case DumFeature::EventTaken:
               stop = true;
               break;
            case DumFeature::FeatureDone:
               *active = false;
               break;
            case DumFeature::FeatureDoneAndEventDone:
            case DumFeature::FeatureDoneAndEventTaken: //??
            case DumFeature::ChainDoneAndEventTaken:
            case DumFeature::ChainDoneAndEventDone:
               *active = false;
               stop = true;
               break;
         }

         if (pres & DumFeature::EventDoneBit)
         {
            delete msg;
            int bits = pres;
            bits ^= DumFeature::EventDoneBit;
            bits |= DumFeature::EventTaken;
            pres = static_cast<DumFeature::ProcessingResult>(bits);
         }
      }

      active++;
      feat++;
   }
   while(!stop && feat != mFeatures.end());


   int chainBits = 0;
   if (pres & DumFeature::ChainDoneBit || feat == mFeatures.end())
   {
      chainBits |= ChainDoneBit;
   }

   if (pres & DumFeature::EventTakenBit)
   {
      chainBits |= EventTakenBit;
   }

   return static_cast<DumFeatureChain::ProcessingResult>(chainBits);
}