#pragma once

// Used so a button takes a context as a parameter (Game, GameRun or Encounter)
// This way a button can call functions from a context without creating several buttons classes for each one
// A button thus holds a function pointer that takes a context as a parameter
class Context
{

};