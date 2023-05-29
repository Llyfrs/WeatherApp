# Weather App

This is application providing user with current information about the weather. 
The data comes from [openweatherAPI](https://openweathermap.org/api). For the program to work properly an
API key from them is required. It can be inserted in the settings.

The main window consists of current weather information and forecast for the next 5 days, more information
for specific day can be shown by hovering your mouse over it, which will cause the info box to update with,
data from that day. 



<p align="center">
  <img src="https://i.imgur.com/nIZ3KdG.png" height="300"/>
</p>


On first launch the application may seem broken, because all text will have dummy values, this is because for the
application to load any data **you need to have your API key inserted**, this can be done in settings window. 
Make sure to press the enter button after inserting your API key, this will test if the key is valid and if it is, 
save it. 

<p align="center">
<img src="https://i.imgur.com/LOzdMer.png">
</p>

Other options available in settings are, choosing in which unit to display temperatures, location selection, and 
setting up update interval (to not use all free calls, 2 updates per minutes are recommended). Location is always selected
based on inserted coordinates, but you can automatically get coordinates for you city by searching it in the location
text bar. Pressing enter will show you results to chose from. 


<p align="center">
<img src="https://i.imgur.com/9vvtXDd.png">
</p>

**Be aware every time you save a settings, have successfully API check or use search location, API call will be used, this is the fastest way to use up all your API calls**

### Requirements 
This project is dependent on the [**curlpp**](http://www.curlpp.org/) and [**nlohmann-json**](https://github.com/nlohmann/json#implicit-conversions) libraries.



