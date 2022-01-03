Clash Helper
-------------------
DESCRIPTION

"Not Clash" is an event that occurs regularly within our friend group. It's a 5 versus 5 gamemode that is based off "Clash" from League of Legends, which is an official tournament that people play in for prizes. This Discord bot will help us coordinate and make teams for the games that we play almost weekly.

-------------------
FILES

- ClashHelper.py

Contains the code required to run a bot that helps coordinate Not Clash games.

- config.py

Contains the parameters required to run ClashHelper.py.

-------------------
INSTRUCTIONS

1. Create a Discord server (https://support.discord.com/hc/en-us/articles/204849977-How-do-I-create-a-server-)
2. Create a Discord application (https://discord.com/developers/applications)
3. Create a Bot for the application (Application_Name -> Bot)
4. Generate the invite link for the bot into your Discord server (Application_Name -> OAuth2 -> Scopes -> Check Bot -> Check Administrator -> Copy Link)
5. Copy and paste link into browser and invite the bot into your Discord server
6. Copy the token for the Discord bot (Application_Name -> Bot -> Token -> Copy)
7. Open terminal
8. Enter ~/ClashHelper repository
9. Create a python file called "config.py" and insert "TOKEN = '<Discord Bot Token>'" within the file
10. Enter "python ClashHelper.py" into terminal
11. Send message !help in the discord server with the bot

-------------------
ADDITIONAL NOTES

- Requires the Discord API to run (https://discordpy.readthedocs.io/en/stable/intro.html)