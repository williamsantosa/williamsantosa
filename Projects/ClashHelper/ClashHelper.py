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

# 10 players separated into 2 groups of 5
def team10(players):
    p_copy = players.copy()
    team1 = []
    team2 = []
    while len(p_copy) > 0:
        index = random.randint(0, len(p_copy) - 1)
        team = random.randint(1,2)
        if team == 1 and len(team1) < 5:
            team1.append(p_copy.pop(index))
        elif team == 2 and len(team2) < 5:
            team2.append(p_copy.pop(index))
        
    return (team1, team2)

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

# Message is sent into a channel response(s)
@client.event
async def on_message(message):
    username = str(message.author).split("#")[0]
    user_message = str(message.content)
    channel = str(message.channel.name)
    lmsg = user_message.lower()

# Run the client on server/machine
client.run(TOKEN)