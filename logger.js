const Discord = require('discord.js');
const bot = new Discord.Client();
const config = require("./config.json");
const token = config.token;
const fs = require('fs');
var log = "log.txt";
var prefix = '!';
var today = new Date();

var dateMsg = "Log updated on " + today.getHours() + " hour " + today.getMinutes() + " minute " + today.getDate() + " "+ (today.getMonth()+1) + " " + today.getFullYear() + "\n";
var fileName = "./" + today.getDate() + today.getMonth() + today.getFullYear() + ".txt";

var log = dateMsg;

bot.on('ready', () => {
    console.log('This bot is online!');
    setInterval(function(){
        fileName = "./" + today.getDate() + today.getMonth() + today.getFullYear() + ".txt";
        fs.writeFile(fileName,"",(err)=>{if(err) throw err;});
        writeToLog();
         //console.log("messages logged");
        },60000); //every 24 hours since bot launch run 
    });
bot.on('message', msg =>{

    log += msg.author + " said " + msg.content + " in channel: " + msg.channel + "\n";

    if (msg.content.indexOf(prefix) !== 0) return;
    if(!msg.member.roles.has('679947682642395147')){
      //console.log('admin used command');
      return; //only allows mods to use commands
    }
    const args = msg.content.slice(prefix.length).trim().split(/ +/g);
    const command = args.shift().toLowerCase();

    if(command === 'logmessages'){
        writeToLog();
    }
})

function writeToLog(){

    log += dateMsg;
    fs.writeFile(fileName, log, (err) => {
        if(err) throw err;
        console.log('logging file: DateMonthYear');
    });
    log = "";
    
}

bot.login(token);
