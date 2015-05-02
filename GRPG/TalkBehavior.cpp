//  Module:             Games Programming
//  Assignment2:        GRPG
//  Student Name:       Jeremy Choo
//  Student Number:     S10132161H

#include "talkBehavior.h"
#include "NPC.h"
#include "UI.h"
#include "grpg.h"

TalkBehavior::TalkBehavior(NPC* i, UI* u, Player* p, Entity* e, Grpg* g){
	ii = i;
	ui = u;
	thePlayer = p;
	entity = e;
	grpg = g;
	gem = g->getGameEventManager();
	questData = g->getQuestLoader()->getQuestData();
}

string TalkBehavior::displayText(){ return "Talk to " + ii->getname(); }
void TalkBehavior::action(){
	VECTOR2 collisionVector;
	if (entity->collidesWith(*thePlayer, collisionVector))
	{
		if (ii->getTalkText().find("detail") == 0)
		{
			ui->removeWindow();
			int detailNumber = stoi(ii->getTalkText().substr(6));
			switch (detailNumber)
			{
				case 1:
				{
					ui->drawWindow("Easter Bunny");
					if (questData->getValue("easterStatus") == 0)
					{
						ui->addTalkText(new ChatInformation("Hello, I'm the easter bunny!", chatNS::RIGHT));
						ui->addTalkText(new ChatInformation("I generally bring easter to the entire world, helping to bring joy through easter eggs to everyone - even the ones that tend to be hostile! I don't show bias to anyone!", chatNS::RIGHT));
						ui->addTalkText(new ChatInformation("Unfortunately, it doesn't seem like there'll be easter today.", chatNS::RIGHT));
						ChatDecision* dt = new ChatDecision(chatNS::VERTICALLY);
						dt->addOption(1, "Why, what's the matter?");
						dt->addOption(2, "Wow, it's the easter bunny! That's amazing!");
						dt->addOption(0, "Uh, I should go. Things to do...");
						dt->setCaller(this);
						ui->addTalkText(dt);
					}
					else if (questData->getValue("easterComplete"))
					{
						ui->addTalkText(new ChatInformation("Hey! Thanks for all your help!", chatNS::RIGHT));
						ChatDecision* dt = new ChatDecision(chatNS::VERTICALLY);
						dt->addOption(6, "About those items you required earlier...");
						dt->addOption(15, "About these easter eggs...");
						dt->addOption(0, "Gotta go, see ya");
						dt->setCaller(this);
						ui->addTalkText(dt);
					}
					else if (questData->getValue("easterStatus") == 3)
					{
						ui->addTalkText(new ChatInformation("I've managed to soothe the bird!", chatNS::LEFT));
						ui->addTalkText(new ChatInformation("So I see. Great job! You've been a big help in getting easter started!", chatNS::RIGHT));
						ui->addTalkText(new ChatInformation("So easter can continue?", chatNS::LEFT));
						ui->addTalkText(new ChatInformation("That's right! Thank you for all your help!", chatNS::RIGHT));
						ui->addTalkText(new ChatInformation("No problem!", chatNS::LEFT));
						ui->addTalkText(new ChatInformation("As a reward, here's a common easter egg for you! Also, you may be able to find some more easter eggs as you kill monsters, since they will also be getting easter eggs and may drop them once killed. You can use these easter eggs for yourself or sell them to me.", chatNS::RIGHT));
						ChatDecision* dt = new ChatDecision(chatNS::VERTICALLY);
						dt->addOption(0, "Thanks!");
						dt->setCaller(this);
						ui->addTalkText(dt);
						gem->informListeners(new GameEvent_EntityAction(ii));
					}
					else if (questData->getValue("foodGiven") && questData->getValue("easterBirdNestStatus") == 3 && questData->getValue("easterEggStatus") == 3)
					{
						ui->addTalkText(new ChatInformation("Hello again!", chatNS::RIGHT));
						ui->addTalkText(new ChatInformation("I've completed all the tasks you've asked me to do!", chatNS::LEFT));
						ui->addTalkText(new ChatInformation("Great job! However, the bird's still looking a bit restless. Perhaps you could help me soothe the bird?", chatNS::RIGHT));
						ui->addTalkText(new ChatInformation("Soothe the bird?", chatNS::LEFT));
						ui->addTalkText(new ChatInformation("Yes, you know, say kind words to it, make it feel better, pet it and stuff. I'm not too good and doing that, maybe you could help me?", chatNS::RIGHT));
						ChatDecision* dt = new ChatDecision(chatNS::VERTICALLY);
						dt->addOption(0, "Alright");
						dt->setCaller(this);
						ui->addTalkText(dt);
						gem->informListeners(new GameEvent_EntityAction(ii));
					}
					else
					{
						ui->addTalkText(new ChatInformation("Hello again!", chatNS::RIGHT));
						ChatDecision* dt = new ChatDecision(chatNS::VERTICALLY);
						dt->setCaller(this);
						generateEasterQuestTalk(dt);
						ui->addTalkText(dt);
					}
					break;
				}
				default:
				{
					ui->addChatText("Developer warning: detail chat was required, but");
					stringstream ss;
					ss << "the following detail number was not found: " << detailNumber;
					ui->addChatText(ss.str());
					break;
				}
			}
		}
		else
		{
			ui->addChatText(ii->getname() + ": " + ii->getTalkText());
		}
	}
	else
	{
		thePlayer->setVictim(entity);
		thePlayer->setNPCAction(this);
	}
}

void TalkBehavior::optionSelected(ChatOption co)
{
	ui->addTalkText(new ChatInformation(co.text, chatNS::LEFT));
	//Note to developers: This method will already initalize the final ChatDecision* here for you. Use it.
	//Caller has been set with a default displayType of VERTICALLY, call the set codes to change it if required
	//If not used, please call delete cd; to ensure that there are no leaks.
	ChatDecision* cd = new ChatDecision(chatNS::VERTICALLY);
	cd->setCaller(this);
	switch (co.id)
	{
	case 0: //Always exit
		ui->removeWindow();
		//No use with cd
		delete cd;
		grpg->attemptQuestCompletions();
		break;
	case 1: //Easter: Asks what's the matter
		ui->addTalkText(new ChatInformation("Well...it's a long story.", chatNS::RIGHT));
		cd->addOption(3, "I have time.");
		cd->addOption(4, "Give me a summary of the story then.");
		cd->addOption(5, "Skip it, tell me what you want");
		cd->addOption(0, "I'm kind of busy at the moment, no time. Gotta go!");
		ui->addTalkText(cd);
		break;
	case 2: //Easter: Asks OMG is the easter bunny
		ui->addTalkText(new ChatInformation("Yes! I bring easter to the entire world, giving out easter eggs!", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Unfortunately, I've had a bit of a problem, so I'm afraid there won't be Easter this year. Maybe even forever.", chatNS::RIGHT));
		cd->addOption(1, "Why, what's the matter?");
		cd->addOption(0, "Uh, I should go. Things to do...");
		ui->addTalkText(cd);
		break;
	case 3: //Easter: Start long speech
		//Split into 2 parts here so that it's easier to read
		//In the middle of this speech the player is prompted for a decision, and both speeches lead back to id 3
		//As such, text is checked here to find out which part to start talking
		if (co.text != "Go on..." && co.text != "A vacuum cleaner? Can't you just head out and buy some?")
		{
			ui->addTalkText(new ChatInformation("Well, I have a magical bird that lays the easter eggs for me to give them out. I keep it healthy and fed, and it lays the eggs.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("Unfortunately, a few months ago my workers decided to riot, due to Civ not having what they want.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("Who's Civ?", chatNS::LEFT));
			ui->addTalkText(new ChatInformation("Civ is a person who comes by to our hidden base every year, offering goods to trade with us.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("He offers amazing items that you take for granted in your world. For example, my workers were expecting him to have a vacuum cleaner to trade, but he didn't.", chatNS::RIGHT));
			cd->addOption(3, "Go on...");
			cd->addOption(3, "A vacuum cleaner? Can't you just head out and buy some?");
			ui->addTalkText(cd);
		}
		else
		{
			if (co.text == "A vacuum cleaner? Can't you just head out and buy some?")
			{
				ui->addTalkText(new ChatInformation("We could, but it would reveal us, and we don't want to do that too often", chatNS::RIGHT));
			}
			ui->addTalkText(new ChatInformation("The workers really wanted the vacuum cleaner because it would help them automatically clean dust and place them into the bag, instead of them having to manually do it themselves.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("Many of them even prepared specially for it, modifying their homes with available electrical sockets.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("However, it turned out that Civ did not offer that item. The workers rioted with this, claiming ridiculous stuff like 'We work, we say!' or something similar.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("Sounds terrible!", chatNS::LEFT));
			ui->addTalkText(new ChatInformation("It was. They blocked off the bird's food storage, annoyed it, and messed up it's nest.", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("Now the bird is too stressed to lay eggs, and unless it does so there won't be easter this year, maybe any more!", chatNS::RIGHT));
			cd->addOption(5, "So, what do you need me to do?");
			cd->addOption(0, "I just remembered there's something I need to do, see you later!");
			ui->addTalkText(cd);
		}
		break;
	case 4: //Easter: Start tl;dr
		ui->addTalkText(new ChatInformation("Well, the basis of it is that my workers have gone through riot, and have messed up my magical bird that lays easter eggs.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("They have blocked off the bird's food storage, annoyed it, and messed up it's nest.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Now the bird is too stressed to lay eggs, and unless it does so there won't be easter this year, maybe any more!", chatNS::RIGHT));
		cd->addOption(5, "So, what do you need me to do?");
		cd->addOption(3, "Sounds like an interesting story. Could you tell me the full story?");
		cd->addOption(0, "I just remembered there's something I need to do, I need to go now.");
		ui->addTalkText(cd);
		break;
	case 5: //Easter: Start quest
		ui->addTalkText(new ChatInformation("I need you to get some feathers somwhere, in order to rebuild the bird's nest so that it is usuable again.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("I also need you to get a sample of an easter egg that has already been sent out.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Finally, I require some cooked rotten meat to feed the bird, it hasn't been fed in a long time since the food supply has gone rotten when it was blocked", chatNS::RIGHT));
		gem->informListeners(new GameEvent_EntityAction(ii));
		cd->addOption(0, "Alright.");
		ui->addTalkText(cd);
		break;
	case 6: //Let's talk about something else
		ui->addTalkText(new ChatInformation("What would you like to know?.", chatNS::RIGHT));
		generateEasterQuestTalk(cd);
		ui->addTalkText(cd);
		break;
	case 7: //Let's talk about the feathers you need
		ui->addTalkText(new ChatInformation("Sure, what do you want to know?", chatNS::RIGHT));
		cd->addOption(8, "What do you need these feathers for?");
		if (questData->getValue("easterBirdNestStatus") != 2)
		{
			cd->addOption(9, "Where do you think I can get these feathers?");
		}
		else
		{
			cd->addOption(9, "I got some feathers, what should I do?");
		}
		cd->addOption(6, "Let's talk about something else");
		ui->addTalkText(cd);
		break;
	case 8: //What do you need these feathers for?
		ui->addTalkText(new ChatInformation("I need the feathers to rebuild the bird's nest to be like his home.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("The bird can't lay eggs without having a proper, comfortable nest after all.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Thus, some feathers need to be gathered to place them at the nest to make it more comfortable.", chatNS::RIGHT));
		if (questData->getValue("easterBirdNestStatus") != 2)
		{
			cd->addOption(9, "Where do you think I can get these feathers?");
		}
		else
		{
			cd->addOption(9, "I got some feathers, what should I do?");
		}
		cd->addOption(6, "Let's talk about something else");
		ui->addTalkText(cd);
		break;
	case 9: //Where do you think I can get these feathers (if haven't gotten it yet)
		if (questData->getValue("easterBirdNestStatus") != 2)
		{
			ui->addTalkText(new ChatInformation("I have no idea where feathers can be easily found. Chickens, perhaps?", chatNS::RIGHT));
			ui->addTalkText(new ChatInformation("I know chickens can be found just near the doctor.", chatNS::RIGHT));
		}
		//I got some feathers, what should I do
		else
		{
			ui->addTalkText(new ChatInformation("Simply interact with the bird's nest to rebuild it.", chatNS::RIGHT));
		}
		cd->addOption(8, "What do you need these feathers for?");
		cd->addOption(6, "Let's talk about something else");
		ui->addTalkText(cd);
		break;
	case 10: //Let's talk about the easter egg you wanted.
		if (questData->getValue("easterEggStatus") == 2)
		{
			ui->addTalkText(new ChatInformation("I have an egg sample for you.", chatNS::LEFT));
			ui->addTalkText(new ChatInformation("You hand over the easter egg to the Easter Bunny.", chatNS::MIDDLE));
			gem->informListeners(new GameEvent_EntityAction(ii));
			ui->addTalkText(new ChatInformation("Thanks! This will help us identify which new eggs we can use!", chatNS::RIGHT));
			generateEasterQuestTalk(cd);
			ui->addTalkText(cd);
		}
		else
		{
			ui->addTalkText(new ChatInformation("Sure, what do you want to know?", chatNS::RIGHT));
			cd->addOption(11, "What do you need these eggs for?");
			cd->addOption(12, "Where do you think I can get the eggs?");
			cd->addOption(6, "Let's talk about something else");
			ui->addTalkText(cd);
		}
		break;
	case 11: //What do you need the easter egg for?
		ui->addTalkText(new ChatInformation("Well, not all eggs from the bird can be used as easter eggs.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Some eggs are of a bad quality, or may not contain what we need inside the egg.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("As such, it is best if we have a sample egg to compare new eggs to, so that we can ensure that we give out the good eggs instead of the bad.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Don't you have any eggs yourself?", chatNS::LEFT));
		ui->addTalkText(new ChatInformation("Unfortunately not, during the riot all remaining eggs I have are destroyed. I will need you to get some back from people that I've given them to.", chatNS::RIGHT));
		cd->addOption(12, "Where do you think I can get the eggs?");
		cd->addOption(6, "Let's talk about something else");
		ui->addTalkText(cd);
		break;
	case 12: //Where do you think I can get the egg?
		ui->addTalkText(new ChatInformation("You might be able to get some back by killing monsters, they may already have gotten an easter egg from me, and will drop it if you kill them.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Alternatively, some people around town may already have them, but they won't be willing to part with them so easily - you may need to use other, less legal means to get them.", chatNS::RIGHT));
		cd->addOption(11, "What do you need these eggs for?");
		cd->addOption(6, "Let's talk about something else");
		ui->addTalkText(cd);
		break;
	case 13: //Let's talk about feeding the bird.
		ui->addTalkText(new ChatInformation("Sure, what do you want to know?", chatNS::RIGHT));
		cd->addOption(14, "What exactly do you need me to do?");
		cd->addOption(6, "Actually, let's talk about something else");
		ui->addTalkText(cd);
		break;
	case 14: //Feeding: What exactly do you need me to do?
		ui->addTalkText(new ChatInformation("I need you to get some cooked rotten meat and feed it to the bird right next to me.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Where can I get them?", chatNS::LEFT));
		ui->addTalkText(new ChatInformation("I think some of the stores around here may sell the meat, or you can kill some of the chickens and cook their meat", chatNS::RIGHT));
		generateEasterQuestTalk(cd);
		ui->addTalkText(cd);
		break;
	case 15: //About these easter eggs.
		ui->addTalkText(new ChatInformation("Ah yes. Thanks to you, I can now start giving out easter eggs to others!", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("As such, during your travels, you may fight enemies that already have an easter eggs. They'll drop them on death.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Easter eggs come in 4 tiers - common, rare, epic and legendary. You can use these easter eggs for yourself or sell them to me.", chatNS::RIGHT));
		cd->addOption(16, "Tell me about the common easter eggs.");
		cd->addOption(17, "Tell me about the rare easter eggs.");
		cd->addOption(18, "Tell me about the epic easter eggs.");
		cd->addOption(19, "Tell me about the legendary easter eggs.");
		cd->addOption(0, "Thanks for the information.");
		ui->addTalkText(cd);
		break;
	case 16: //Tell me about the common easter eggs.
		ui->addTalkText(new ChatInformation("The common easter eggs are fairly common, and are likely the easter egg you will see the most.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("These easter eggs will restore 2HP once they are eaten. However, don't be fooled by their low rarity and low healing, they have a special property", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("And what would that be?", chatNS::LEFT));
		ui->addTalkText(new ChatInformation("They stack! They're common, stackable healing food! You can store pretty much limitless amount of healing in that single slot!", chatNS::RIGHT));
		cd->addOption(17, "Tell me about the rare easter eggs.");
		cd->addOption(18, "Tell me about the epic easter eggs.");
		cd->addOption(19, "Tell me about the legendary easter eggs.");
		cd->addOption(0, "Thanks for the information.");
		ui->addTalkText(cd);
		break;
	case 17: //Tell me about the rare easter eggs.
		ui->addTalkText(new ChatInformation("These easter eggs are significantly rarer and harder to find, however you can just buy one from me if you want one.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Their rarity is somewhat offset by their unique effect - they can be used to grant XP in a random skill!", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("That's amazing!", chatNS::LEFT));
		ui->addTalkText(new ChatInformation("I know! Additionally, if you get 4 common eggs in a row while killing monsters, the next egg you get is guaranteed to be a rare or better!", chatNS::RIGHT));
		cd->addOption(16, "Tell me about the common easter eggs.");
		cd->addOption(18, "Tell me about the epic easter eggs.");
		cd->addOption(19, "Tell me about the legendary easter eggs.");
		cd->addOption(0, "Thanks for the information.");
		ui->addTalkText(cd);
		break;
	case 18: //Tell me about the epic easter eggs.
		ui->addTalkText(new ChatInformation("The epic easter eggs are very rare and hard to find, but if your really want one you can purchase one from me.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("They will give you a teleport back to this town once used.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("So they can be used as an emergency escape?", chatNS::LEFT));
		ui->addTalkText(new ChatInformation("That's right! They work everywhere too!", chatNS::RIGHT));
		cd->addOption(16, "Tell me about the common easter eggs.");
		cd->addOption(17, "Tell me about the rare easter eggs.");
		cd->addOption(19, "Tell me about the legendary easter eggs.");
		cd->addOption(0, "Thanks for the information.");
		ui->addTalkText(cd);
		break;
	case 19: //Tell me about the legendary easter eggs.
		ui->addTalkText(new ChatInformation("Ah, the legendary easter eggs. Many never get one in their lifetime.", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("However, they have amazing effects to make up for their rarity. For starters, they will restore all of your health! I won't spoil the remaining effects for you, you'll have to find them out yourself!", chatNS::RIGHT));
		ui->addTalkText(new ChatInformation("Ah, but if I really want one without having to leave my fate to RNGesus I can just buy one from you right?", chatNS::LEFT));
		ui->addTalkText(new ChatInformation("That is correct!", chatNS::RIGHT));
		cd->addOption(16, "Tell me about the common easter eggs.");
		cd->addOption(17, "Tell me about the rare easter eggs.");
		cd->addOption(18, "Tell me about the epic easter eggs.");
		cd->addOption(0, "Thanks for the information.");
		ui->addTalkText(cd);
		break;
	default:
		stringstream ss;
		ss << "Warning: Unknown ChatData ID: " << co.id;
		ui->addChatText(ss.str());
		//Also doesn't use cd
		delete cd;
		break;
	}
}

void TalkBehavior::generateEasterQuestTalk(ChatDecision* cd)
{
	cd->addOption(7, "Let's talk about the feathers you need.");
	cd->addOption(10, "Let's talk about the easter egg that you need.");
	cd->addOption(13, "Let's talk about feeding the bird");
	cd->addOption(0, "Tasks to do, gotta go");
}