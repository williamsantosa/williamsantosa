import discord
import random
import config as cfg

TOKEN = cfg.TOKEN
client = discord.Client()

@client.event
async def on_ready():
    print("We have logged in as {0.user}".format(client))

client.run(TOKEN)