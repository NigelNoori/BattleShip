# EVOLUTION.md

## Overview
This document outlines the key changes made to the Battleship REST system throughout development, based on debugging, restructuring, and alignment with REST and microservice design principles.

---

## 1. Migration to ShapeREST Architecture
- Refactored the original text-based Battleship implementation into a REST-based microservice system.
- Organized the project into separate services:
  - gameServer
  - randomAiServer
  - centerAiServer
  - sweepAiServer
- Adopted controller-service-dto structure for better separation of concerns.

---

## 2. REST Endpoint Implementation
- Implemented core REST endpoints:
  - GET /game/state
  - POST /game/place
  - POST /game/fire
  - GET /game/winner
- Added proper HTTP status handling (200 and 400 responses).
- Ensured JSON request/response formatting using Oat++ DTOs.

---

## 3. Ship Tracking and Game Logic Improvements
- Introduced ShipRecord structure to track:
  - ship name
  - size
  - health
  - destroyed status
- Implemented:
  - hit detection
  - destroy detection
  - winner detection
- Updated fire logic to return:
  - "Hit <ShipName>"
  - "Destroyed <ShipName>"
  - "Miss"

---

## 4. Additional CRUD Endpoints
Added new endpoints to extend functionality:
- GET /game/ships/{player}/health
- GET /game/ships/{player}/destroyed
- GET /game/current-player
- GET /game/stats
- POST /game/reset
- DELETE /game/ship/{player}/{row}/{col}

These endpoints improve observability and control of the game state.

---

## 5. Error Handling Improvements
- Added validation for:
  - invalid player values
  - invalid coordinates
  - invalid request body
  - duplicate shot attempts
- Standardized error responses using MessageDto.

---

## 6. AI Microservice Integration
- Connected gameServer to AI services:
  - randomAiServer
  - centerAiServer
  - sweepAiServer
- Implemented gateway endpoints:
  - GET /ai/random/shot
  - GET /ai/center/shot
  - GET /ai/sweep/shot
- Ensured communication between services via HTTP requests.

---

## 7. Build and Compilation Fixes
- Fixed Makefile issues across services.
- Resolved missing file paths and incorrect include directives.
- Corrected compilation errors related to DTO usage and string handling.

---

## 8. Swagger Adjustments
- Temporarily disabled Swagger to resolve runtime crashes.
- Prepared system for re-enabling Swagger with correct resource paths.

---

## 9. Stability and Testing
- Fixed server crashes caused by improper DTO initialization.
- Verified endpoints using curl:
  - game state retrieval
  - ship placement
  - firing logic
  - AI endpoints
- Ensured servers run concurrently without failure.

---

## Conclusion
The system evolved from a basic text-based implementation into a fully functional REST-based microservice architecture. Major improvements include structured API design, robust game logic, microservice integration, and improved error handling.