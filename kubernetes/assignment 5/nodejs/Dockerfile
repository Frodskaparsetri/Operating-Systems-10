# This is to make the older docker engines use the buildkit (newer engines use it by default)
# (just good practice)

# syntax=docker/dockerfile:1

# Specifies what predefined kernel you wish to run it from
FROM node:15-alpine

# creates a directory called app, 
# and everything from here on out is added to the /app folder within the docker image
WORKDIR /app

# copying the package.json into the /app folder
## the reason we copy only the package.json, followed by an install, THEN we copy the rest
## is because of how the layered caching functions in docker
COPY package.json .

# run executes a command, as you would in your terminal
## this specicially installs all the required dependencies
RUN yarn --production

# copies everything from the local folder to the docker image 
# (but is added to the /app folder due to the workdir being set before)
COPY . .

# CMD lets you define a default command to run when your container starts
## in this case it is to execute the index.js file in node
CMD ["node", "index.js"]