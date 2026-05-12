#ifndef PROFILE_HPP_INCLUDED
#define PROFILE_HPP_INCLUDED

#include <string>
#include <vector>

namespace model {

/** Single user profile with name and win/loss record */
struct Profile {
  std::string name;
  int wins;
  int losses;
};

/** Manages profiles: add, list, update, delete; persists to file */
class ProfileManager {
 public:
  explicit ProfileManager(const std::string& filepath = "profiles.txt");

  std::vector<Profile> list() const;
  bool add(const std::string& name);
  bool update(const std::string& name, int wins, int losses);
  bool remove(const std::string& name);
  Profile* find(const std::string& name);
  const Profile* find(const std::string& name) const;

  void recordWin(const std::string& name);
  void recordLoss(const std::string& name);
  bool save();

 private:
  std::string filepath_;
  std::vector<Profile> profiles_;
  bool load();
};

}  // namespace model

#endif  // PROFILE_HPP_INCLUDED
