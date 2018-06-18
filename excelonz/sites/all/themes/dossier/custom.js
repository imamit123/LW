
jQuery(document).ready(function(){

         
	jQuery('.notification_link').toggle(
		function(){
			jQuery('#block-golive-golive-user-ref').slideDown('slow');
		},
		function(){
			jQuery('#block-golive-golive-user-ref').slideUp('slow');
		}
	);
           
        // Accept and Reject
        jQuery('#golive-acc-rej').submit(function () {
            return false;
        });
        
        jQuery('#golive-acc-rej input').click(function(){
            jQuery('#golive-acc-rej input').type = 'button'; 
            var input_val = jQuery(this).val();
            var input_nid = jQuery(this).attr('name');
            jQuery.ajax({
               url:Drupal.settings.basePath +"notification_save",
               data:{status:input_val,nid:input_nid}
            });
            jQuery(this).parent().hide();   
            jQuery(this).parent().parent().append('<p class="txt_wrap" style="color: #FFFFFF;font-size: 20px;padding-top: 10px;text-align: center;">Status Update</p>');
			setTimeout("jQuery('p.txt_wrap').hide()", 2000);
        });
});

(function ($) {
    Drupal.behaviors.assessments = {
        attach: function (context, settings) {
		  golive_mcq_submit ();
		  golive_tf_submit ();
		  golive_fib_submit ();
		  hide_next ();
		  //grab_val ();
		jQuery('.ans_d').css('display','none');
		jQuery('.desc p').css('display','none');
		jQuery('.desc p').click(function() {
			jQuery('.ans_d').slideDown('slow');
		});
     }
  }
}) (jQuery);

jQuery(document).ready(function(){
	jQuery('#submit-button').click(function() {
		//alert('clicked');
		jQuery('.button-option input').click(function() {
			//alert('clicked');
			var a = jQuery(this).attr('id');
			jQuery('.give_val').append(a);
		});
	jQuery('#golive-form .mcq .radio-option input#Correct').parent().css({'background':'green','color':'#fff'});
	var textarea_val = jQuery('.give_val').text();
		if (textarea_val == 'Wrong'){
			jQuery('.desc p').css('display','block');
		}

    jQuery('.radio-option input').attr('disabled','true');
	jQuery('#edit-next').show();
	jQuery('.button-option #Correct').css({'background':'green','color':'#fff'});
	golive_fib_check ();
	});

	jQuery('#edit-next').click(function() {
		jQuery('#reset').attr('disabled','false');
		$('.button-option input').click(function() {
			var a = $(this).attr('id');
			$('.give_val').append(a);
		});
	});
	
	golive_fib_check ();
});


function hide_next () {
  jQuery('#edit-next').hide();
}


function golive_mcq_submit () {

	jQuery('#golive-form #submit-button').attr('disabled','disabled');
	jQuery('#golive-form .radio-option input').click ( function () {
		jQuery('#submit-button').removeAttr('disabled');
		jQuery('#golive-form .give_val').empty();
		//alert('Test this');
		var mcq_click = jQuery(this).attr('id');
		//alert(mcq_click);
		jQuery('#golive-form .give_val').text(mcq_click);
	});
}

function golive_tf_submit () {
	jQuery('#golive-form #submit-button').attr('disabled','disabled');
	jQuery('#golive-form .tf_questions input').click ( function () {
		jQuery('#submit-button').removeAttr('disabled');
		jQuery('#golive-form .tf_questions input').attr('disabled','disabled');
		var tf_click = jQuery(this).attr('id');
		//alert(mcq_click);
		jQuery('#golive-form .give_val').text(tf_click);
	});
}

function golive_fib_submit () {
	jQuery('#golive-form #submit-button').attr('disabled','disabled');
	jQuery('#golive-form #fib_expected_bt').click ( function () {
		jQuery('#submit-button').removeAttr('disabled');
	});
}

function golive_fib_check () {
	// Go live fib form
	var golive_fib_correct_bt = jQuery('#golive-form .fib #fib_correct_bt').val().toLowerCase();
	var golive_fib_expected_bt = jQuery('#golive-form .fib #fib_expected_bt').val().toLowerCase();
	if( golive_fib_correct_bt != golive_fib_expected_bt ){
		jQuery('#golive-form .fib #fib_expected_bt').css({'background':'red','color':'#fff'});
		jQuery('#golive-form .fib #fib_correct_bt').empty();
		jQuery('#golive-form .fib #fib_correct_bt').append('Wrong');
	}
	if( golive_fib_correct_bt == golive_fib_expected_bt){
		jQuery('#golive-form .fib #fib_expected_bt').css({'background':'green','color':'#fff'});
		jQuery('#golive-form .fib #fib_correct_bt').empty();
		jQuery('#golive-form .fib #fib_correct_bt').append('Correct')
	}
}




