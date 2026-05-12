#!/bin/bash

echo "Reset game"
curl -s -X POST http://localhost:8000/game/reset | python3 -m json.tool

echo "\nPlace Player 1 ship"
curl -s -X POST http://localhost:8000/game/place \
-H "Content-Type: application/json" \
-d '{"player":1,"shipName":"Destroyer","row":0,"col":0,"orientation":"H"}' | python3 -m json.tool

echo "\nPlace Player 2 ship"
curl -s -X POST http://localhost:8000/game/place \
-H "Content-Type: application/json" \
-d '{"player":2,"shipName":"Cruiser","row":1,"col":1,"orientation":"V"}' | python3 -m json.tool

echo "\nGame state"
curl -s http://localhost:8000/game/state | python3 -m json.tool

echo "\nFire shot"
curl -s -X POST http://localhost:8000/game/fire \
-H "Content-Type: application/json" \
-d '{"attacker":1,"defender":2,"row":1,"col":1}' | python3 -m json.tool

echo "\nShip health"
curl -s http://localhost:8000/game/ships/2/health | python3 -m json.tool

echo "\nDestroyed ships"
curl -s http://localhost:8000/game/ships/2/destroyed | python3 -m json.tool

echo "\nStats"
curl -s http://localhost:8000/game/stats | python3 -m json.tool

echo "\nAI Random"
curl -s http://localhost:8000/ai/random/shot | python3 -m json.tool

echo "\nAI Center"
curl -s http://localhost:8000/ai/center/shot | python3 -m json.tool

echo "\nAI Sweep"
curl -s http://localhost:8000/ai/sweep/shot | python3 -m json.tool
