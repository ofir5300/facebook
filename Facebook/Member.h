#pragma once
//
//  Member.hpp
//  Facebook
//
//  Created by Ofir Cohen on 25/11/2018.
//  Copyright � 2018 Ilan Kushnir. All rights reserved.
//

#ifndef __Member_h
#define __Member_h

#include "Entity.h"
#include "Date.h"
#include "Time.h"
#include "Status.h"
///////////////////

class Fanpage;
class Status;

class Member : public Entity
{
private:
    //attributes
//    char        name[NAME_MAX_SIZE];
    Date*       birthDate;
//    Status**    statuses = nullptr;
//    int         statusesCount = 0;
//    int         statusesArrSize = 0;
//    Member**    friends = nullptr;
    int         friendsCount = 0;
//    int         friendsArrSize = 0;
//    Fanpage**   fanPages = nullptr;
    int         fanPagesCount = 0;
//    int         fanPagesArrSize = 0;
    
    
public:
    // Constructor, Distructor
    Member(char* name, Date* birthDate) : Entity(name)
    {
        this->birthDate = birthDate;
    }
    
    ~Member()
    {
        delete birthDate;
    }
    
    // Methods
    Status**            getStatuses()            const;
    int                 getStatusesCount();
    Status**            getRecentStatuses()      const;    // using getStatuses() to fetch 10 (or less) recent statuses
    Status**            getAllFriendsRecentStatuses()   const;  // returns an array of the 10 most recent statuses of all member's friends
    Status*             getMostRecentStatus();
    Status**            fetchFriendsStatuses()   const;
    bool                addFriend(Member* newFriend);
    bool                addFanPage(Fanpage* newFanPage);
    bool                addStatus(Status* newStatus);
    Fanpage**           getFanPages()      const;
    Member**            getFriends()       const;
    int                 getFriendsCount();
    char*               getName();
    Date*               getBirthDate()     const;
    virtual void        printEntity()      const override;
};



#endif /* Member_h */


















