/***************************************************************************
 *   Copyright (C) 2009-2010 by Savoir-Faire Linux                         *
 *   Author : Jérémy Quentin <jeremy.quentin@savoirfairelinux.com>         *
 *            Emmanuel Lepage Vallee <emmanuel.lepage@savoirfairelinux.com>*
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef CONTACT_H
#define CONTACT_H

#include <QtGui/QListWidgetItem>
#include <QtGui/QWidget>

#include <kabc/addressee.h>
#include <kabc/picture.h>
#include <kabc/phonenumber.h>

#include "Item.h"
#include "ContactItemWidget.h"

using namespace KABC;

class ContactItemWidget;

/**
   @author Jérémy Quentin <jeremy.quentin@savoirfairelinux.com>
*/
class Contact : public QObject, public Item<ContactItemWidget>{
private:
   QString firstName;
   QString secondName;
   QString nickName;
   QString phoneNumber;
   Picture * photo;
   PhoneNumber::Type type;
   bool displayPhoto;
   
public:

   //Constructors & Destructors
   Contact(Addressee addressee, const PhoneNumber & number, bool displayPhoto);
   ~Contact();
   
   //Getters
   QString getPhoneNumber() const;
   QString getNickName() const;
   QString getFirstName() const;
   QString getSecondName() const;
   const Picture * getPhoto() const;
   PhoneNumber::Type getType() const;
   void initItem();
   
protected:
   void initItemWidget();

};

#endif
