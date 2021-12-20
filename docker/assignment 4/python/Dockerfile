# This is to make the older docker engines use the buildkit (newer engines use it by default)
# (just good practice)

# syntax=docker/dockerfile:1

# Specifies what predefined kernel you wish to run it from
FROM python:3.8-slim-buster

# creates a directory called app, 
# and everything from here on out is added to the /app folder within the docker image
WORKDIR /app

# copies everything from the local folder to the docker image 
# (but is added to the /app folder due to the workdir being set before)
COPY . .

# run executes a command, as you would in your terminal
## this specicially installs all the required dependencies
RUN pip3 install -r requirements.txt

# CMD lets you define a default command to run when your container starts
## in this case it is to execute the python rest server using the flask library
CMD [ "python3", "-m" , "flask", "run", "--host=0.0.0.0", "--port=3000"]