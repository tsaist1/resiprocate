#ifndef Helper_hxx
#define Helper_hxx


#include <sipstack/SipMessage.hxx>
#include <sipstack/Symbols.hxx>

namespace Vocal2
{

class Helper
{
   public:

      const static int tagSize;  //bytes in to-tag& from-tag, should prob. live
      //somewhere else

      //in general content length handled automatically by SipMessage?

      static SipMessage* makeInvite(const NameAddr& target,
                                   const NameAddr& from,
                                   const NameAddr& contact);


      static SipMessage* makeForwardedInvite(const SipMessage& invite);

      static SipMessage* makeResponse(const SipMessage& request, int responseCode);

      static SipMessage* makeResponse(const SipMessage& request, int responseCode, const NameAddr& myContact);

      //to, maxforwards=70, requestLine& cseq method set, cseq sequence is 1
      static SipMessage* makeRequest(const NameAddr& target, MethodTypes method); // deprecated

      //to, maxforward=70, requestline created, cseq method set, cseq sequence
      //is 1, from and from tag set, contact set, CallId created
      //while contact is only necessary for requests that establish a dialog,
      //those ar the requests most likely created by this method, others will
      //be generated by the dialog.
      static SipMessage* makeRequest(const NameAddr& target, 
                                    const NameAddr& from,
                                    const NameAddr& contact,
                                    MethodTypes method);
           

      //creates to, from with tag, cseq method set, cseq sequence is 1
      static SipMessage* makeRegister(const NameAddr& proxy,
                                     const NameAddr& aor);

      static SipMessage* makeFailureAck(const SipMessage& request, const SipMessage& response);
      
      static Data computeUniqueBranch();
      static Data computeProxyBranch(const SipMessage& request);

      static Data computeCallId();
      static Data computeTag(int numBytes);
};
 
}

#endif



/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
