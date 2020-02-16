//===================================|| T E M P L A T E  F U N C T I O N ||===================================

// D stands for Deck's Cards. D can be GreenCard or BlackCard
// E stands for Enum. 
template <class D , typename E>
// Pushes <total> times , <E type> objects in the given <deck>
void pushNtimes(std::shared_ptr < std::deque< std::shared_ptr < D > > > deck , 
  std::unordered_map<std::string , std::vector<uint16_t> >::iterator j ,const E type ,
  const uint16_t & total , uint16_t & times  , const uint16_t & max_per_pers = 0,
  const std::shared_ptr < std::vector< std::string >> cardTexts = nullptr ) {

  uint16_t temp = total;
  while (temp--)
  {
    if (j->second.size() == 6) {  // Follower
      deck->push_back (std::dynamic_pointer_cast<D>( std::make_shared< Follower >(j->first , j->second[0] , j->second[1] ,
      j->second[2] , j->second[3] , cardTexts->at(times) , j->second[4] , j->second[5] , (const FollowerType) type , max_per_pers) ) );
    }
    else if (j->second.size() == 7) {  // Item
      deck->push_back (std::dynamic_pointer_cast<D>(std::make_shared< Item >(j->second[6] , j->first , j->second[0] , j->second[1] ,
      j->second[2] , j->second[3] , cardTexts->at(times) , j->second[4] , j->second[5] , (const ItemType) type , max_per_pers)));
    }
    else if (j->second.size() == 4) {  // Personality
      deck->push_back (std::dynamic_pointer_cast<D>(std::make_shared< Personality >(j->first , j->second[0] , j->second[1] ,
      j->second[2] , j->second[3] , (const PersonalityType) type)));
    }
    else if (j->second.size() == 2) {  // Holding
        if (j->first == "MINE")
          deck->push_back (std::dynamic_pointer_cast<D>(std::make_shared < Mine >(j->first , j->second[0] , j->second[1])));  
        else if (j->first == "GOLD_MINE")
          deck->push_back (std::dynamic_pointer_cast<D>(std::make_shared < GoldMine >(j->first , j->second[0] , j->second[1])));
        else if (j->first == "CRYSTAL_MINE")
          deck->push_back (std::dynamic_pointer_cast<D>(std::make_shared < CrystalMine >(j->first , j->second[0] , j->second[1])));    
        else 
          deck->push_back (std::dynamic_pointer_cast<D>(std::make_shared < Holding >(j->first , j->second[0] , j->second[1] , (const HoldingType) type)));
    }
    times++;
  }
}