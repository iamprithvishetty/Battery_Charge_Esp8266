/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
    },

    // deviceready Event Handler
    //
    // Bind any cordova events here. Common events are:
    // 'pause', 'resume', etc.
    onDeviceReady: function() {
        this.receivedEvent('deviceready');
		window.addEventListener("batterystatus", onBatteryStatus, false);
		cordova.plugins.backgroundMode.enable();
    },

    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');

        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);
    }
};

app.initialize();

function onBatteryStatus(status) {
	let addr = "http://192.168.4.1/command";
	document.getElementById("battery_level").innerHTML = status.level.toString();
	document.getElementById("battery_status").innerHTML = status.isPlugged.toString();
	let batt_lev= status.level.toString();
	let batt_status = status.isPlugged.toString()
	sendAjax(addr,batt_lev,batt_status);
}


function sendAjax(addr,p,v) {
  $.ajax({
    method: "POST",
    url: addr,
    data: {pin: p, value: v}
  });
}

function getPresetValue()
{	
	let addr = "http://192.168.4.1/command";
	let preset_val = document.getElementById("preset_level").value;
	sendAjax(addr,preset_val,"preset");
	document.getElementById("presetlevel").innerHTML= preset_val;
}

function getThresholdValue()
{	
	let addr = "http://192.168.4.1/command";
	let thresh_val = document.getElementById("threshold_level").value;
	sendAjax(addr,thresh_val,"threshold");
	document.getElementById("thresholdlevel").innerHTML= thresh_val;
}
