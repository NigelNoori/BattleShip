#ifndef battleship_game_ProfileService_hpp
#define battleship_game_ProfileService_hpp

#include "dto/ProfileDto.hpp"
#include <string>
#include <vector>

namespace battleship { namespace game { namespace service {

class ProfileService {
private:
  static constexpr const char* PROFILES_FILE = "profiles.txt";

  struct ProfileRecord {
    std::string name;
    int wins;
    int losses;
  };

  std::vector<ProfileRecord> loadAll() const;
  void saveAll(const std::vector<ProfileRecord>& profiles) const;

public:
  oatpp::Object<ProfileListDto>   getAllProfiles() const;
  oatpp::Object<ProfileDto>       getProfile(const std::string& name) const;
  oatpp::Object<ProfileDto>       createProfile(const std::string& name);
  oatpp::Object<ProfileDto>       recordWin(const std::string& name);
  oatpp::Object<ProfileDto>       recordLoss(const std::string& name);
};

}}}

#endif
