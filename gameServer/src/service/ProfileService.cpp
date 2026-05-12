#include "ProfileService.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace battleship { namespace game { namespace service {

// ── file format: one line per profile  "name wins losses" ──────────────────

std::vector<ProfileService::ProfileRecord> ProfileService::loadAll() const {
  std::vector<ProfileRecord> records;
  std::ifstream file(PROFILES_FILE);
  if (!file.is_open()) return records;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    std::istringstream iss(line);
    ProfileRecord r;
    int w = 0, l = 0;
    if (iss >> r.name >> w >> l) {
      r.wins   = w;
      r.losses = l;
      records.push_back(r);
    }
  }
  return records;
}

void ProfileService::saveAll(const std::vector<ProfileRecord>& profiles) const {
  std::ofstream file(PROFILES_FILE, std::ios::trunc);
  for (const auto& r : profiles) {
    file << r.name << " " << r.wins << " " << r.losses << "\n";
  }
}

// ── helpers ─────────────────────────────────────────────────────────────────

static oatpp::Object<ProfileDto> toDto(const ProfileService::ProfileRecord& r) {
  auto dto    = ProfileDto::createShared();
  dto->name   = r.name.c_str();
  dto->wins   = r.wins;
  dto->losses = r.losses;
  return dto;
}

// ── public API ───────────────────────────────────────────────────────────────

oatpp::Object<ProfileListDto> ProfileService::getAllProfiles() const {
  auto result      = ProfileListDto::createShared();
  result->profiles = oatpp::Vector<oatpp::Object<ProfileDto>>::createShared();
  for (const auto& r : loadAll()) {
    result->profiles->push_back(toDto(r));
  }
  return result;
}

oatpp::Object<ProfileDto> ProfileService::getProfile(const std::string& name) const {
  auto records = loadAll();
  for (const auto& r : records) {
    if (r.name == name) return toDto(r);
  }
  return nullptr;
}

oatpp::Object<ProfileDto> ProfileService::createProfile(const std::string& name) {
  auto records = loadAll();
  for (const auto& r : records) {
    if (r.name == name) return toDto(r); // already exists — return existing
  }
  ProfileRecord nr{ name, 0, 0 };
  records.push_back(nr);
  saveAll(records);
  return toDto(nr);
}

oatpp::Object<ProfileDto> ProfileService::recordWin(const std::string& name) {
  auto records = loadAll();
  for (auto& r : records) {
    if (r.name == name) {
      r.wins++;
      saveAll(records);
      return toDto(r);
    }
  }
  // Auto-create if not found
  ProfileRecord nr{ name, 1, 0 };
  records.push_back(nr);
  saveAll(records);
  return toDto(nr);
}

oatpp::Object<ProfileDto> ProfileService::recordLoss(const std::string& name) {
  auto records = loadAll();
  for (auto& r : records) {
    if (r.name == name) {
      r.losses++;
      saveAll(records);
      return toDto(r);
    }
  }
  ProfileRecord nr{ name, 0, 1 };
  records.push_back(nr);
  saveAll(records);
  return toDto(nr);
}

}}}
