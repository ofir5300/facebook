//
//  Member.cpp
//  Facebook
//
//  Created by Ofir Cohen on 25/11/2018.
//  Copyright � 2018 Ilan Kushnir. All rights reserved.
//

#include "Member.h"

Member& Member::operator+=(Member& other)
{
	this->addFriend(&other);
	other.addFriend(this);

	return *this;
}

int Member::getFriendsCount()
{
	return friendsCount;
}

vector<Status*> Member::getAllFriendsRecentStatuses() const
{
	Status* MostRecentStatusTempPtr = nullptr;
	int i, j, currRecentIndex = 0, compareResult, arrIndex = 0;
	
	//creating friend's statuses indices tracking
	vector<int> statusIndices;
	vector<Member*> friends = this->getFriends;
	vector<Member*>::iterator itr = friends.begin(), itrEnd = friends.end();

	for (; itr != itrEnd; ++itr)
	{
		statusIndices.push_back((*itr)->getStatusesCount() - 1);
	}


	///////////////////////////
	//initialising recent statuses arr
	vector<int>::iterator indicesItr = statusIndices.begin(), indicesItrEnd = statusIndices.end();
	vector<Status*> recentStatuses;
	itr = friends.begin();

	for (i = 0; i < RECENT_STATUSES; i++)
	{
		MostRecentStatusTempPtr = nullptr;
		for (j = 0 ; indicesItr != indicesItrEnd; ++indicesItr) // check each friends
		{
			if ((*indicesItr) != -1 && MostRecentStatusTempPtr == nullptr)	//increase J and itr
			{
				MostRecentStatusTempPtr = (*itr)->getStatuses()[(*indicesItr)];		//connection[j]??
				currRecentIndex = j;
			}
			else if ((*indicesItr) != -1)
			{
				compareResult = MostRecentStatusTempPtr->compare((*itr)->getStatuses()[(*indicesItr)]);

				if (compareResult == -1)
				{
					MostRecentStatusTempPtr = (*itr)->getStatuses()[(*indicesItr)];
					currRecentIndex = j;
				}
			}
			j++;
			++itr;
		}

		if (MostRecentStatusTempPtr)
		{
			recentStatuses.push_back(MostRecentStatusTempPtr);
			indicesItr = statusIndices.begin();
			for (i = 0; i < currRecentIndex; i++)
				++indicesItr;
			(*indicesItr) -= 1;
		}


	}
	/* creating friend's statuses indices tracking
	int* statusIndices = new int(friendsCount);
	int* membersInd = new int(friendsCount);
	for (i = 0; i < connectionsCount && arrIndex < friendsCount; i++)
	if (typeid(*(connections[i])) == typeid(Member))
	{
	membersInd[arrIndex] = i;
	statusIndices[arrIndex++] = (connections[i]->getStatusesCount()) - 1;
	}
	/*/////////

	/*/ initialising recent statuses arr
	Status** recentStatuses = new Status*[RECENT_STATUSES];
	for (i = 0; i < RECENT_STATUSES; i++)
	recentStatuses[i] = nullptr;

	// [ 3 | -1 | 2 | 0 ]
	for (i = 0; i < RECENT_STATUSES; i++) {
		MostRecentStatusTempPtr = nullptr;
		for (j = 0; j < friendsCount; j++) {
			if (statusIndices[j] != -1 && MostRecentStatusTempPtr == nullptr)
			{   // point on friend 'j' recent status if no status pointed yet
				MostRecentStatusTempPtr = connections[membersInd[j]]->getStatuses()[statusIndices[j]];
				currRecentIndex = j;
			}
			else if (statusIndices[j] != -1)
			{   // compare pointed status with friends 'j; recent one
				compareResult = MostRecentStatusTempPtr->compare(connections[membersInd[j]]->getStatuses()[statusIndices[j]]);

				if (compareResult == -1)
				{ // if friend 'j' status is newer than the current pointed status
					MostRecentStatusTempPtr = connections[membersInd[j]]->getStatuses()[statusIndices[j]];
					currRecentIndex = j;
				}
			}
		}

		if (MostRecentStatusTempPtr != nullptr)
		{
			recentStatuses[i] = MostRecentStatusTempPtr;
			statusIndices[currRecentIndex] --;
		}
	}

	if (recentStatuses[0] == nullptr) {
		// if there are no friends to this member or no statuses for existing friends
		return nullptr;
	}
	return recentStatuses;
	*/

	return recentStatuses;
}

bool Member::addFriend(Member* newFriend)
{
	addConnection(newFriend);
	friendsCount++;

	return true;
}

bool Member::addFanPage(Fanpage* newFanPage)
{
	addConnection((Entity*)newFanPage);
	fanPagesCount++;

	return true;
}

vector<Fanpage*> Member::getFanPages() const
{
	/*
	Fanpage** fanPages = (fanPagesCount) ? new Fanpage*[fanPagesCount] : nullptr;
	int counter = 0;

	for (int i = 0; (i < connectionsCount) && (counter < fanPagesCount); i++) {
		Entity* currConnection = connections[i];
		if (currConnection && (typeid(*currConnection) == typeid(Fanpage))) {
			fanPages[counter++] = (Fanpage*)connections[i];
		}
	}
	*/
	vector<Fanpage*> fanPages;
	vector<Entity*>::iterator itr = connections.begin();
	vector<Entity*>::iterator itrEnd = connections.end();

	for (; itr != itrEnd; ++itr)
	{
		if (typeid(*(*itr)) == typeid(Fanpage))
			fanPages.push_back((Fanpage*)*itr);
	}

	return fanPages;
}

vector<Member*>  Member::getFriends() const
{
	/*
	Member** friends = (friendsCount) ? new Member*[friendsCount] : nullptr;
	int counter = 0;

	for (int i = 0; (i < connectionsCount) && (counter < friendsCount); i++) {
		Entity* currConnection = connections[i];
		if (currConnection && (typeid(*currConnection) == typeid(Member))) {
			friends[counter++] = (Member*)connections[i];
		}
	}
	*/
	vector<Member*> friends;
	vector<Entity*>::iterator itr = connections.begin();
	vector<Entity*>::iterator itrEnd = connections.end();

	//if (connections.empty())
	//	return nullptr;			//?

	for (; itr != itrEnd; ++itr)
	{
		if (typeid(*(*itr)) == typeid(Member))
		{
			friends.push_back((Member*)*itr);
		}
	}

	return friends;
}

Date* Member::getBirthDate() const
{
	return birthDate;
}


void Member::printEntity() const
{
	Entity::printEntity();
	cout << "Birth Date: " << birthDate->getDateStr() << "\n";
}
