/*
 *  Copyright (C) 2007 Savoir-Faire Linux inc.
 *  Author: Pierre-Luc Beaudoin <pierre-luc.beaudoin@savoirfairelinux.com>
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
 
#ifndef INSTANCE_H
#define INSTANCE_H

#include "instance-glue.h"
#include <dbus-c++/dbus.h>

    
class Instance
: public org::sflphone::SFLphone::Instance_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{
private:
  int count;

public:
  Instance(DBus::Connection& connection);
  static const char* SERVER_PATH;
  
  void Register( const int32_t& pid, const std::string& name ); 
  void Unregister( const int32_t& pid );
  int32_t getRegistrationCount( void );
    
};


#endif//INSTANCE_H