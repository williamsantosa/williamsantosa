# SCP Searcher

### DESCRIPTION

The acronym "SCP" refers to the vast amount of anomalies catalogued in [The SCP Foundation](https://en.wikipedia.org/wiki/SCP_Foundation). Most of these anomalies are secured and contained within an SCP facility in order to protect the general public from their potentially dangerous effects. With this bot, you can search and find the documentation of each SCP with the hyperlink given.

---
### FILES

SCPSearcher.py

- Contains the code required to run a bot that returns the SCP wiki page for specified SCP.

Config.py

- Contains the parameters required to run SCPSearcher.py.

---
### INSTRUCTIONS

1. Create a Discord server (https://support.discord.com/hc/en-us/articles/204849977-How-do-I-create-a-server-)
2. Create a Discord application (https://discord.com/developers/applications)
3. Create a Bot for the application (Application_Name -> Bot)
4. Generate the invite link for the bot into your Discord server (Application_Name -> OAuth2 -> Scopes -> Check Bot -> Check Administrator -> Copy Link)
5. Copy and paste link into browser and invite the bot into your Discord server
6. Copy the token for the Discord bot (Application_Name -> Bot -> Token -> Copy)
7. Open terminal
8. Enter ~/SCPSearcher repository
9. Create a python file called "config.py" and insert "TOKEN = '<Discord Bot Token>'" within the file
10. Enter "python SCPSearcher.py" into terminal
11. Send message !help in the discord server with the bot
