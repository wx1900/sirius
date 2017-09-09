
 <!-- Supersized Background Images -->
jQuery(function($){
				
				$.supersized({
				
				startwidth: 1024,  
                startheight: 768,  
					// Functionality
					slide_interval          :   1000,		// Length between transitions
					transition              :   1, 			// 0-None, 1-Fade, 2-Slide Top, 3-Slide Right, 4-Slide Bottom, 5-Slide Left, 6-Carousel Right, 7-Carousel Left
					transition_speed		:	10000,		// Speed of transition
															   
					// Components							
					slide_links				:	'blank',	// Individual links for each slide (Options: false, 'num', 'name', 'blank')
					slides 					:  	[			// Slideshow Images
														{image : src="images/bg.jpg"}
												]
					
				});
		    });

 

$(document).ready(function(){
	$(" #supersized img").css("display", "none");
    $(" #supersized img").fadeIn(800);
 
}); 