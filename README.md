# Battery_Charge_Esp8266
 
 ## Setting Up Cordova In Windows
 
 #### Download and install Node.js. On installation you should be able to invoke node and npm on your command line.
        https://nodejs.org/en/download/
        
 #### Install the cordova module using npm utility of Node.js. The cordova module will automatically be downloaded by the npm utility.
       C:\>npm install -g cordova
       
 #### Install Java jdk in your device and set path in Environment Variables
       https://www.oracle.com/java/technologies/javase-jdk15-downloads.html
   ##### 1)Once done go to Control Panel System Settings
   ##### 2)Advance Settings --> Environment Variables
   ##### 3)Click New 
       Variable Name: Path
       Variable Value : Inside your Java folder go to jdk go to bin and copy the address and paste 
       e.g Variable Value : C:\Program Files\Java\jdk1.8.0_261\bin
       Click OK
       
#### Install Android Studios
      https://developer.android.com/studio
   ##### 1)Once Installed and setup go to File --> Settings --> Appearance and Behaviour --> System Settings --> Android SDK
   ##### 2) Download all the required SDK versions
    
#### Create the App in cmd
##### Go to the directory where you maintain your source code, and create a cordova project:
      cordova create hello com.example.hello HelloWorld
##### Add the platforms
      cordova platform add android
##### Add the necessary plugins
      cordova plugin add cordova-plugin-battery-status
      cordova plugin add cordova-plugin-background-mode
##### Build The App
      cordova build android
##### The problem with Android Pie AJAX
       https://medium.com/mindorks/my-network-requests-are-not-working-in-android-pie-7c7a31e33330
   ##### Android Pie uses https and blocks http so manually we have to set the settings
   ###### You just need to create a network_security_config file in the xml folder and then include it in the manifest in the following manner.
      <?xml version="1.0" encoding="utf-8"?>
      <manifest ... >
          <application android:networkSecurityConfig="@xml/network_security_config"
                          ... >
              ...
          </application>
      </manifest>
   ###### The network_security_config file looks like this.
    <?xml version="1.0" encoding="utf-8"?>
    <network-security-config>
        <domain-config cleartextTrafficPermitted="true">
            <domain includeSubdomains="true">Http Local Server</domain>
        </domain-config>
    </network-security-config>
  Here you can simply mention the domain name of your server or all the domain names that are using HTTP.
###### Setting Android SDK LOWER AND HIGHER LEVEL
	In cofig.xml change 
	<preference name="android-minSdkVersion" value="22" />
	<preference name="android-targetSdkVersion" value="29" />
  
  
   

      
      
