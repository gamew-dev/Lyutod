...
## 0.6
### Major Codebase Refactor

## 0.6.1
- minor bug fixes and improvement

## 0.6.2
- Reorganize internal files and directory
- Minor improvement

## 0.6.3
- Added config option for each guild
- Open for invite
- Bot intent update

## 0.6.4
- Added User_info command
- Autorole foundation

## 0.6.5
- Added AutoRole command
- Synchronize guild

## 0.6.6
- Added foundation for chatbot ai
- Minor improvement

## 0.6.7 
### Added Ai chatbot feature

## 0.6.8
- Added passive memory and session
    - passive memory using json file stored externally
    - session for 5 minutes i/o cooldown

## 0.6.9
- Fixed Shutdown command logic
    - added countdown logic (now, 15s, 4m, default:60s)
    - shutdown status is global shared and affect some feature
- Fixed ai memory session
    - server session and user session saved separately, including dm's
    - fixed minor prompt issues

## 0.6.10
### 0.6 Stable version
This version marks the final release of version 0.6.x branch. The core logic    
has satisfied enough for initial design goals and any further development would   
need to modify some of the main logic files.
### Whats new
- Guild sync databases
   An admin command used to update guild config
- Guild member count
   An admin command for creating a cencuss voice channel
- Small minor improvement
    - Changed bot default timer from 5 minutes to 10
    - Chatbot timer prompt text

## 0.7
### 0.7.x Base version
First stable version and base version for future developtment of 0.7 branch  
This base version introduce a major refactor of slashcommand with grouping  
and subcommand support.
### Whats new
- Major slashcommand update
   Rewriten slashcommand logic and structure
- Codebase restructuring and preparations for cleaner developtment
    - Memory management refactor
    - Terminal control expansion
    - Some minor logic improvements

## 0.7.1
- New workplace setup
    - Added CMakeLists 
- Feature: Reworked chatbot prompt message with edit and silent ability
- Feature: Chatbot slashCommand
    - Ability to check history and user memory
- Fix: Chatbot session memory corrupt
- Fix: Button event caching
