import discord
import config as cfg

TOKEN = cfg.TOKEN
client = discord.Client()

# Prints the client to terminal
@client.event
async def on_ready():
    print("Logged in as {0.user}".format(client))

# Message is sent into a channel response(s)
@client.event
async def on_message(message):
    username = str(message.author).split("#")[0]
    user_message = str(message.content)
    channel = str(message.channel.name)
    lmsg = user_message.lower()

    # See messages sent in the server in terminal
    print(f"{username}: {user_message} ({channel})")

    # Check for if the message sender is the bot and end the program if so
    if message.author == client.user:
        return

    # Help command
    if lmsg == "!help":
        await message.channel.send("Use !scp <number> to return the wiki entry for said SCP")
        return
    # Search and return the link for an SCP entry with error check
    elif lmsg.split(" ")[0] == "!scp" and len(lmsg.split(" ")) == 2:
        n = lmsg.split(" ")[1]
        # Check if entry is valid or not
        try:
            int(n)
        except ValueError:
            return
        if int(n) < 0:
            n = n[1:]
        await message.channel.send(f"https://scp-wiki.wikidot.com/scp-{n}")
        return

# Run the client on server/machine
client.run(TOKEN)