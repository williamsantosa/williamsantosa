import discord
import random
import config as cfg

TOKEN = cfg.TOKEN
client = discord.Client()

# Prints the client to terminal
@client.event
async def on_ready():
    print("Logged in as {0.user}".format(client))
    

# Helper functions

# Return a list of the players in each team
# If uneven, will place into the first team, then the next, etc
def teamSort(players, n):
    # Create copy of players
    p_copy = players.copy()

    # Initialize dictionary containing all the teams and the players
    teams = {} # Team Number : List of players
    for i in range(n):
        teams[i] = []

    # Sort until everything is full
    currTeam = 0
    while len(p_copy) > 0:
        # Put player into team and remove from list of players
        index = random.randint(0, len(p_copy) - 1)
        teams[currTeam].append(p_copy.pop(index))

        # Increment and reset if needed
        currTeam = currTeam + 1
        if currTeam >= n:
            currTeam = 0
        
    return teams

# Return a list of the players in each team and their roles
# Will only work if there are 10 players
def leagueSort(players):
    # Error check for if not 10 players
    if len(players) != 10:
        return

    # Initialize team 1 and team 2
    # Player : Role
    t1 = {}
    t2 = {} 

    # Create teams with their roles and place in each respective dictionary
    roles = ["Top","Jungle","Mid","Bot","Support"]
    teams = teamSort(players, 2)
    for player in teams[0]:
        t1[player] = roles.pop(random.randint(0, len(roles) - 1))
    roles = ["Top","Jungle","Mid","Bot","Support"]
    for player in teams[1]:
        t2[player] = roles.pop(random.randint(0, len(roles) - 1))
    
    return (t1, t2)

# Message is sent into a channel response(s)
@client.event
async def on_message(message):
    username = str(message.author).split("#")[0]
    user_message = str(message.content)
    channel = str(message.channel.name)
    lmsg = user_message.lower()

    # See messages sent in the server in terminal
    print(f"{username}: {user_message} ({channel})")
    
    # Help command and create variable for message put lowercase
    listmsg = lmsg.split(" ")
    if lmsg == "!help":
        await message.channel.send("```!team <number of teams> player1 player2 ... to create teams\n!league player1 player2 ... to create teams with roles for League of Legends 5v5 customs```")
        return
        
    # Any number of teams and players
    elif listmsg[0] == "!team":
        # Obtain number of teams
        n = listmsg[1]
        # Get players and sort the teams
        players = listmsg[2:]
        teams = teamSort(players, int(n))
        msg = ""
        # Print out the teams in Discord
        for team in teams:
            t = team + 1
            msg = msg + f"Team {t}\n"
            for player in teams[team]:
                msg = msg + "- " + player.capitalize() + "\n"
            msg = msg + "\n"

        # Send message in Discord
        await message.channel.send("```" + msg + "```")
        return

    # Specifically for League of Legends 5v5, returns the player and the role within each team
    elif listmsg[0] == "!league":
        players = listmsg[1:]
        if(len(players) != 10):
            await client.get_channel(message.channel.id).send(f"Please input 10 names. You inputted {len(players)} names.")
            return
        teams = leagueSort(players)
        msg = ""
        t = 1
        # Print out the teams in Discord
        for team in teams:
            msg = msg + f"Team {t}\n"
            for player in team:
                msg = msg + "- " + player.capitalize() + " | " + team[player] + "\n"
            msg = msg + "\n"
            t = t + 1

        # Send message in Discord
        await message.channel.send("```" + msg + "```")
        return

# Run the client on server/machine
client.run(TOKEN)