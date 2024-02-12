# Reciplease  
### CSCI 201 Group Project (Team 9)


## Project Videos
[Reciplease Demo Video](https://drive.google.com/file/d/1-DTT5_hdruA6I3asji0HsUiLTy0SdIrn/view?usp=share_link)

[Reciplease Text-Stack Presentation](https://drive.google.com/file/d/1fcdL_nVnH1FGKAgsCJxmdgQuqbfmmykU/view?usp=share_link)


## Running the Web App

This project uses a React frontend and Java Servlet backend with a Google Cloud SQL database.

### 1. clone the repo

Before you start, download node.js if you do not already have it by clicking [here](https://nodejs.org/en/download/). 
Clone this repo. 

### 2. start the Java backend Tomcat server

Open Eclipse and import the 201-Group-Project -> backend -> Assignment4Backend folder as a Dynamic Web Project. 
Start the Tomcat server and run the Assignment4Backend project on the server. 

### 3. start the React frontend

Open Visual Studio Code and import the entire 201-Group-Project repo. 
If your backend Tomcat server is not running on port 8080, you must change the port connection in the frontend project to match.
1. Open `axios.js` (frontend -> src -> api -> axios.js) and change the port to match your Tomcat server port. 
2. Open `messages-page.js` (frontend -> src -> pages -> Messages-Page -> messages-page.js) and update the port in the url on line 10. 
Open a terminal and navigate into the `frontend` folder.  
Run `npm install` to install all dependencies. 
Run `npm start` to start the project.  
The react app will run on localhost using port 3000: [http://localhost:3000](http://localhost:3000). 
NOTE: if your browser has CORS enabled, the frontend will have trouble connecting to the backend. To fix this problem, scroll down to troubleshooting to see how to disable CORS. 

### 4. test the app!

## Troubleshooting

### CORS Error

If you get an error that says something like:  
'Access to XMLHttpRequest ... from origin ... has been blocked by CORS policy..."
This just means there is some Cross Origin errors from communicating on two different ports.
I have not figured out if this is a backend or frontend issue yet but was able to bypass the problem by diabling CORS in chrome.
To do this: 
1. open your computer terminal 
2. run this command: 
`open -n -a /Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome --args --user-data-dir="/tmp/chrome_dev_test" --disable-web-security`
3. a new chrome tab should open up and you can just reopen the app by going to [http://localhost:3000](http://localhost:3000).

