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
        
# Message is sent into a channel response(s)
@client.event
async def on_message(message):
    username = str(message.author).split("#")[0]
    user_message = str(message.content)
    channel = str(message.channel.name)
    lmsg = user_message.lower()

# Run the client on server/machine
client.run(TOKEN)