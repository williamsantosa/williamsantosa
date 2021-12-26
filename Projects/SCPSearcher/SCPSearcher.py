import discord
import random
import config as cfg

TOKEN = cfg.TOKEN
client = discord.Client()

@client.event
async def on_ready():
    print("Logged in as {0.user}".format(client))

@client.event
async def on_message(message):
    username = str(message.author).split("#")[0]
    user_message = str(message.content)
    channel = str(message.channel.name)
    print(f"{username}: {user_message} ({channel})")

    if message.author == client.user:
        return
    
    lmsg = user_message.lower()

    if lmsg == "!help":
        await message.channel.send(f'Hello {username}!')
    elif lmsg.split(" ")[0] == "!scp" and len(lmsg.split(" ")) == 2:
        n = lmsg.split(" ")[1]
        await message.channel.send(f"https://scp-wiki.wikidot.com/scp-{n}")

@client.event
async def shutdown(context):
    exit()

client.run(TOKEN)