#include "model/Profile.hpp"
#include <fstream>
#include <algorithm>
#include <cctype>

namespace model {

ProfileManager::ProfileManager(const
    std::string& filepath) : filepath_(filepath) {
  load();
}

bool ProfileManager::load() {
  profiles_.clear();
  std::ifstream f(filepath_);
  if (!f.good()) return true;
  std::string name;
  int wins = 0;
  int losses = 0;
  while (f >> name >> wins >> losses) {
    Profile p;
    p.name = name;
    p.wins = wins;
    p.losses = losses;
    profiles_.push_back(p);
  }
  return true;
}

bool ProfileManager::save() {
  std::ofstream f(filepath_);
  if (!f.good()) return false;
  for (size_t i = 0; i < profiles_.size(); i++) {
    f << profiles_[i].name << " " << profiles_[i].wins << " "
      << profiles_[i].losses << "\n";
  }
  return true;
}

std::vector<Profile> ProfileManager::list() const {
  return profiles_;
}

bool ProfileManager::add(const std::string& name) {
  if (name.empty()) return false;
  for (size_t i = 0; i < name.size(); i++) {
    if (std::isspace(static_cast<unsigned char>(name[i]))) return false;
  }
  if (find(name) != nullptr) return false;
  Profile p;
  p.name = name;
  p.wins = 0;
  p.losses = 0;
  profiles_.push_back(p);
  return save();
}

bool ProfileManager::update(const std::string& name, int wins, int losses) {
  Profile* p = find(name);
  if (p == nullptr) return false;
  p->wins = wins;
  p->losses = losses;
  return save();
}

bool ProfileManager::remove(const std::string& name) {
  auto it = std::find_if(profiles_.begin(), profiles_.end(),
      [&name](const Profile& p) { return p.name == name; });
  if (it == profiles_.end()) return false;
  profiles_.erase(it);
  return save();
}

Profile* ProfileManager::find(const std::string& name) {
  for (size_t i = 0; i < profiles_.size(); i++) {
    if (profiles_[i].name == name) return &profiles_[i];
  }
  return nullptr;
}

const Profile* ProfileManager::find(const std::string& name) const {
  for (size_t i = 0; i < profiles_.size(); i++) {
    if (profiles_[i].name == name) return &profiles_[i];
  }
  return nullptr;
}

void ProfileManager::recordWin(const std::string& name) {
  Profile* p = find(name);
  if (p != nullptr) {
    p->wins++;
    save();
  }
}

void ProfileManager::recordLoss(const std::string& name) {
  Profile* p = find(name);
  if (p != nullptr) {
    p->losses++;
    save();
  }
}

}  // namespace model
