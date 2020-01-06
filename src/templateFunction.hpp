//===================================|| T E M P L A T E  F U N C T I O N ||===================================

// D stands for Deck's Cards. D can be GreenCard or BlackCard
// E stands for Enum. 
template <class D , typename E>
// Pushes <total> times , <D type> objects in the given <deck>
void pushNtimes(std::shared_ptr < std::queue< std::shared_ptr < D > > > deck , std::unordered_map<std::string , std::vector<size_t> >::iterator j ,const E type  , size_t total , size_t * times ) {

  size_t temp = total;
  while (temp--)
  {
    if (j->second.size() == 6) {  // Follower
      deck->push (std::dynamic_pointer_cast<D>( std::make_shared< Follower >(j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , "Random Text" , j->second[4] , j->second[5] , (const enum FollowerType)type , total) ) );
    }
    else if (j->second.size() == 7) {  // Item
      deck->push (std::dynamic_pointer_cast<D>(std::make_shared< Item >(j->second[6] , j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , "Random Text" , j->second[4] , j->second[5] , (const enum ItemType)type , total)));
    }
    else if (j->second.size() == 4) {  // Personality
      deck->push (std::dynamic_pointer_cast<D>(std::make_shared< Personality >(j->first , j->second[0] , j->second[1] , j->second[2] , j->second[3] , (const enum PersonalityType)type)));
    }
    else if (j->second.size() == 2) {  // Holding
        if (j->first == "MINE")
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < Mine >(j->first , j->second[0] , j->second[1])));  
        else if (j->first == "GOLD_MINE")
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < GoldMine >(j->first , j->second[0] , j->second[1])));
        else if (j->first == "CRYSTAL_MINE")
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < CrystalMine >(j->first , j->second[0] , j->second[1])));    
        else 
          deck->push (std::dynamic_pointer_cast<D>(std::make_shared < Holding >(j->first , j->second[0] , j->second[1] , (const enum HoldingType)type)));
    }
    (*times)++;
  }
}
