/*
 *  Copyright (C) 2006-2009 Savoir-Faire Linux inc.
 *
 *  Author: Emmanuel Milou <emmanuel.milou@savoirfairelinux.com>
 *  Author: Alexandre Bourget <alexandre.bourget@savoirfairelinux.com>
 *  Author: Yan Morin <yan.morin@savoirfairelinux.com>
 *                                                                              
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *                                                                                
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                              
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef SIPACCOUNT_H
#define SIPACCOUNT_H

#include "account.h"
#include "sipvoiplink.h"
#include "pjsip/sip_transport_tls.h"
#include "pjsip/sip_types.h"

class SIPVoIPLink;

/**
 * @file sipaccount.h
 * @brief A SIP Account specify SIP specific functions and object (SIPCall/SIPVoIPLink)
 */

class SIPAccount : public Account
{
    public:
        /**
         * Constructor
         * @param accountID The account identifier
         */
        SIPAccount(const AccountID& accountID);

        /* Copy Constructor */
        SIPAccount(const SIPAccount& rh);

        /* Assignment Operator */
        SIPAccount& operator=( const SIPAccount& rh);

        /**
         * Virtual destructor
         */
        virtual ~SIPAccount();

        /** 
         * Actually unuseful, since config loading is done in init() 
         */
        void loadConfig();

        /**
         * Initialize the SIP voip link with the account parameters and send registration
         */ 
        int registerVoIPLink();

        /**
         * Send unregistration and clean all related stuff ( calls , thread )
         */
        int unregisterVoIPLink();

        inline void setCredInfo(pjsip_cred_info *cred) {_cred = cred;}
        inline pjsip_cred_info *getCredInfo() {return _cred;}
        
        inline void setContact(const std::string &contact) {_contact = contact;}
        inline std::string getContact() {return _contact;}
                
        inline std::string& getAuthenticationUsername(void) { return _authenticationUsername; }
        inline void setAuthenticationUsername(const std::string& username) { _authenticationUsername = username; }
        
        inline bool isResolveOnce(void) { return _resolveOnce; }
        
        inline std::string& getRegistrationExpire(void) { return _registrationExpire; }
        
        bool fullMatch(const std::string& username, const std::string& hostname);
        bool userMatch(const std::string& username);
        bool hostnameMatch(const std::string& hostname);

        pjsip_regc* getRegistrationInfo( void ) { return _regc; }
        void setRegistrationInfo( pjsip_regc *regc ) { _regc = regc; }

        inline int getCredentialCount(void) { return _credentialCount; }
        
        /* Registration flag */
        bool isRegister() {return _bRegister;}
        void setRegister(bool result) {_bRegister = result;}        
        
        inline pjsip_tls_setting * getTlsSetting(void) { return _tlsSetting; }
        inline bool isTlsEnabled(void) { return (_transportType == PJSIP_TRANSPORT_TLS) ? true: false; }
        inline pj_uint16_t getPort(void) { return (pj_uint16_t) atoi(_port.c_str()); }

        /*
         * @return pj_str_t "From" uri based on account information.
         * From RFC3261: "The To header field first and foremost specifies the desired
         * logical" recipient of the request, or the address-of-record of the
         * user or resource that is the target of this request. [...]  As such, it is
         * very important that the From URI not contain IP addresses or the FQDN
         * of the host on which the UA is running, since these are not logical
         * names."
         */
        pj_str_t getFromUri(void);
        
        /*
         * This method adds the correct scheme, hostname and append
         * the ;transport= parameter at the end of the uri, in accordance with RFC3261.
         * It is expected that "port" is present in the internal _hostname.
         *
         * @return pj_str_t "To" uri based on @param username
         * @param username A string formatted as : "username"
         */
        pj_str_t getToUri(const std::string& username);

        /*
         * In the current version of SFLPhone, "srv" uri is obtained in the preformated 
         * way: hostname:port. This method adds the correct scheme and append
         * the ;transport= parameter at the end of the uri, in accordance with RFC3261.
         *
         * @return pj_str_t "server" uri based on @param hostPort
         * @param hostPort A string formatted as : "hostname:port"
         */
        pj_str_t getServerUri(void);
               
        /*
         * @param port Optional port. Otherwise set to the port defined for that account.
         * @param hostname Optional local address. Otherwise set to the hostname defined for that account.
         * @return pj_str_t The contact header based on account information
         */
        pj_str_t getContactHeader(const std::string& address, const std::string& port);
        
    private:
        /* Maps a string description of the SSL method 
         * to the corresponding enum value in pjsip_ssl_method.
         * @param method The string representation 
         * @return pjsip_ssl_method The corresponding value in the enum
         */
        pjsip_ssl_method sslMethodStringToPjEnum(const std::string& method);
    
        /*
         * Initializes tls settings from configuration file.
         *
         */  
        void initTlsConfiguration(void);  
 
        /*
         * Initializes set of additional credentials, if supplied by the user.
         */
        int initCredential(void);       
        
        /**
         * Credential information
         */
        pjsip_cred_info *_cred;

        /**
         * The pjsip client registration information
         */
        pjsip_regc *_regc;
        
        std::string _port;
        
        pjsip_transport_type_e _transportType;
        
        /**
        *  The TLS settings, if tls is chosen as 
        *  a sip transport. 
        */ 
        pjsip_tls_setting * _tlsSetting;	
                         
        /**
         * To check if the account is registered
         */
        bool _bRegister;
        
        bool _resolveOnce;
                
        /*
         * SIP address
         */
        std::string _contact;
        
        std::string _displayName;
        
        std::string _registrationExpire;
        
        std::string _authenticationUsername;
        
        std::string _realm;
        
        int _credentialCount;
};

#endif