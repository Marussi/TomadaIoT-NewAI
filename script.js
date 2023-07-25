var firebaseConfig = {
    apiKey: "AIzaSyCiWzUN_YGfA6ZN-NzaQM0ruJxawyDCpTU",
    authDomain: "tomada-iot-inteligente.firebaseapp.com",
    databaseURL: "https://tomada-iot-inteligente-default-rtdb.firebaseio.com",
    projectId: "tomada-iot-inteligente",
    storageBucket: "tomada-iot-inteligente.appspot.com",
    messagingSenderId: "440040942459",
    appId: "1:440040942459:web:6e9669f32da9c9d5866bde",
    measurementId: "G-GG8LNC0FVQ"
  };
  
  
  firebase.initializeApp(firebaseConfig);

$(document).ready(function(){
    var database = firebase.database();
	var ReleStatus;
	

	database.ref().on("value", function(snap){
		ReleStatus = snap.val().ReleStatus;
		if(ReleStatus == "1"){    

			document.getElementById("unact").style.display = "none";
			document.getElementById("act").style.display = "block";
		} else {
			
			document.getElementById("unact").style.display = "block";
			document.getElementById("act").style.display = "none";
		}
	});

    $(".toggle-btn").click(function(){
		var firebaseRef = firebase.database().ref().child("ReleStatus");

		if(ReleStatus == "1"){    
			firebaseRef.set("0");
			ReleStatus = "0";
		} else {
			firebaseRef.set("1");
			ReleStatus = "1";
		}
	})

	
});