bool Player::close_game(){
    if(get_hosted_game()!=nullptr) {
      hosted_game.reset();
        return true;}
    return false;}

 bool Player::host_game(std::string s, Mode m) {
        if(s.empty()) throw std::runtime_error{"empty string"};
        if(this->hosted_game == nullptr){
        switch (m){
            case Mode::Ranked:
                hosted_game = std::make_shared<RGame>(s, shared_from_this());
                return true;

            case Mode::Unranked:
                hosted_game = std::make_shared<UGame>(s, shared_from_this());
                return true;
                }
        } return false; }

