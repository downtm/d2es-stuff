#ifndef _BUFFME_H_
#define _BUFFME_H_

#include <vector>
#include <unordered_map>
#include "../../Includes/D2Client.h"

enum BuffStates
{
	STATE_SENDING,
	STATE_WAITINGFORAFFECT,
	STATE_IDLE,
};

struct BuffData
{
	BuffData(int buffId, int affectId, const std::string &name) 
	{
		this->buffId = buffId;
		this->affectId = affectId;
		this->name = name;
	}

	int buffId;
	int affectId;
	std::string name;
};

class BuffMe
{
	public:
		BuffMe();
		void Start(bool useChat);
		void OnAffect(size_t affectID);
		void OnDisAffect(size_t affectID);
		void OnTick();
		void NextBuff();
	private:
		void CastCurrentBuff();
		void OnCompletion();
		bool ReadBuffs(const std::string &fileName);

		std::vector<BuffData> desiredBuffs;
		size_t currentBuffIndex;

		BuffStates currentState;
		bool needsRebuff;
		bool useChat;
		int startingSkill;
};

#endif