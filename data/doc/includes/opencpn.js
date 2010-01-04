


//-- concertina menu options --
function openMenu(menu_option) {

	if ( menu_option == 'Intro' ) {
		if (	document.getElementById("sub_menu_intro").style.display == "block") 
			document.getElementById("sub_menu_intro").style.display = "none";
		else 	document.getElementById("sub_menu_intro").style.display = "block";
		document.getElementById("sub_menu_using_ocpn").style.display = "none";
		document.getElementById("sub_menu_navigation").style.display = "none";
		document.getElementById("sub_menu_features").style.display = "none";
	}
	
	if ( menu_option == 'Getting Started' ) {

		document.getElementById("sub_menu_intro").style.display = "none";
		if (	document.getElementById("sub_menu_using_ocpn").style.display == "block")
			document.getElementById("sub_menu_using_ocpn").style.display = "none";
		else	document.getElementById("sub_menu_using_ocpn").style.display = "block";
		document.getElementById("sub_menu_navigation").style.display = "none";
		document.getElementById("sub_menu_features").style.display = "none";
	}
	
	if ( menu_option == 'Navigation' ) {

		document.getElementById("sub_menu_intro").style.display = "none";
		document.getElementById("sub_menu_using_ocpn").style.display = "none";
		if (	document.getElementById("sub_menu_navigation").style.display == "block")
			document.getElementById("sub_menu_navigation").style.display = "none";
		else	document.getElementById("sub_menu_navigation").style.display = "block";
		document.getElementById("sub_menu_features").style.display = "none";
	}
	
	if ( menu_option == 'Features' ) {

		document.getElementById("sub_menu_intro").style.display = "none";
		document.getElementById("sub_menu_using_ocpn").style.display = "none";
		document.getElementById("sub_menu_navigation").style.display = "none";
		if (	document.getElementById("sub_menu_features").style.display == "block")
			document.getElementById("sub_menu_features").style.display = "none";
		else	document.getElementById("sub_menu_features").style.display = "block";

	}

}



//-- redundant code ??? --
function admin_login() {
	document.getElementById("login_message").innerHTML="working";
}