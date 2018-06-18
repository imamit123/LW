/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


(function ($) {
  Drupal.behaviors.basic = {
  	attach: function (context, settings) {
  		jQuery( '.answer-option li.j_word' ).draggable();
  		jQuery( '.answer-option li.match' ).draggable({ disabled: false });
    	jQuery('.btn-wrap').removeAttr('style');
      jQuery('.btn-wrap').css('display','none');
      jQuery('.answer_link .descs p,.answer_link .descs .ans_desc').hide();
      remove_div ();
			aggr_width = jQuery('.queston_img img').width();
			if (aggr_width >450){
				jQuery('.question-text').css({'float':'left','width':'100%'});
				jQuery('.question_div').css('margin-top','0px');
			}
			else {
				jQuery('.question_div').css('margin-top','120px');
				jQuery('.question-text').css({'background':'#fff','display':'inline'});
			}
			//match_display();
			//drag_drop();
			fibkeypress ();
			fib_buttons ();
			jQuery('.final_txt').remove();
			if (jQuery('#fib_expected .userenter')) {
					jQuery('#fib_expected .userenter:first').focus();
			}
			/* Remove js for match
				jQuery('.left_ex_block li').live('mouseover',function(){
					jQuery(this).draggable();
				});
			*/
			jQuery('.clrtxt').click(function() {
				jQuery('.userenter').val('');
				jQuery('#fib_expected .userenter:first').focus();
				jQuery('.desc_wrap.fib .btn-wrap').hide();
			});

				jQuery('.mtfclear').live('click',function() {
					jQuery('.dragClass').show();
					jQuery('.box-area.placeholder').empty();

					jQuery('.desc_wrap .btn-wrap').hide();
					jQuery('.desc_wrap .btn-wrap *').hide();
			});


			jQuery('.jumbtxt').live('click',function() {

				jQuery('.drag-area.jumbd ol').empty();
				jQuery('.current').empty();
				jQuery('.current').text('User Input');
				jQuery('.desc_wrap.jumb .btn-wrap').hide();
//@newcode
				jQuery('.jumble_question_wrap .answer-option li').removeClass('dragClass').show();
				jQuery('.jumble_question_wrap .answer-option li').draggable({ disabled: false });
			});
			jQuery('#fib_expected .userenter.one:last').keyup(function() {
				jQuery('#fib_expected .userenter.two:first').focus();
			});
			jQuery('#fib_expected .userenter.two:last').keyup(function() {
				jQuery('#fib_expected .userenter.three:first').focus();
			});
			if(jQuery('#golive-form .right_exl_block').length > 0) {
				auto_height ();
			}
			a = jQuery('#assessments-form .assessment-header .oness').last().text();
			jQuery('.assessment-header .oness').hide();
			jQuery('#assessments-form .desc_wrap').append('<div class="testdiv"><p>'+a+'</p></div>');
			//setTimeout("jQuery('.testdiv').remove()", 2000);
			if(jQuery('.testdiv p').text() === ''){
    			jQuery('.testdiv').remove();
			}

			/* Remove blurb anywhere click */
			jQuery('body *').click(function () {
    			jQuery('.desc_wrap .testdiv').remove();
			});
		}
  }
}) (jQuery);



jQuery(document).ready(function(){
	jQuery( '.answer-option li.match' ).draggable({ disabled: false });
	var mcq_val = 0;
	question_wrap ();
	reset_btn();
	grab_val ();
	submit_action ();
	jQuery('#lvl_txt_block').remove()
	jQuery('.answer_link .descs p,.answer_link .descs .ans_desc').hide();
	jQuery('.btn-wrap').hide();
	jQuery('.button-option').live('click', function (){
		jQuery(this).css('background','#73c200');
		jQuery(this).addClass('clicked');
		jQuery('.button-option').bind('click', false);
	});
	jQuery('.final_txt').remove();
	jQuery('#edit-next').click(function() {
		jQuery('#reset').attr('disabled','false');
		$('.button-option input').click(function() {
			var clicked_mcq = $(this).attr('id');
			$('.give_val').append(clicked_mcq );
		});
	});


	jQuery('#edit-finish').live('click',function() {
		//console.log("finish 1");
		deletechecked();
		return false;
	});
});


function deletechecked(message) {
	console.log("delete checked");
   var answer = confirm('Are you sure, you want to finish this session ?')
   if (answer){
         jQuery('#edit-timer-value').val(cur_time);

       document.messages.submit();
   }
   return false;
}

function grab_val () {
	jQuery('.answer-option .input_class ').live('click',function() {
			//alert('clicked');
			var mcq_val = jQuery(this).attr('id');
	});
}

function question_wrap () {
	jQuery('.button-option .input_class').live('click',function() {
	  jQuery('.desc_wrap .btn-wrap').css('display','block');
		jQuery('.desc_wrap .btn-wrap-inner').css('display','block');
		jQuery('.desc_wrap .btn-wrap-inner p').css('display','block');
		jQuery('.desc_wrap .btn-wrap-inner #reset').css('display','block');
		jQuery('.desc_wrap .btn-wrap-inner #submit-button').css('display','block');
		var a = jQuery(this).attr('id');
		jQuery('.give_val').append(a);
	});
}

function reset_btn () {

	jQuery('.btn-wrap-inner button#reset').live('click',function() {
		jQuery( '.give_val' ).empty();
		jQuery('.box-area.placeholder').empty();
		jQuery( '.keyarea .give_val' ).val('');
		jQuery('.current').empty();
		jQuery('.current').text('User Input');
		jQuery('.desc_wrap .btn-wrap').hide();
		jQuery('.desc_wrap .btn-wrap *').hide();
		jQuery('.userenter').val('');
		jQuery('.mergeval').html('');
		jQuery('.button-option').removeAttr('style');
		jQuery('.button-option .input_class').removeAttr("disabled");
		jQuery('.drag-area.col2').removeAttr('style');
		if (jQuery('#fib_expected .userenter')) {
			jQuery('#fib_expected .userenter:first').focus();
		}
		jQuery('.question_wrap .button-option').removeClass('clicked');
		jQuery('.button-option').unbind('click');

		jQuery('.dragClass').show();
	});
}

function submit_action () {
	jQuery('.btn-wrap-inner button#submit-button').live('click',function() {
		match_individual_check ();
		jQuery('.button-option').removeAttr('style');
		jQuery('.button-option #Correct').css('background','#73C200');
		jQuery('.button-option #Correct').parent().css('background','#73C200');
		jQuery('.button-option.clicked #Wrong').css('background','#ec3324');
		jQuery('.button-option.clicked #Wrong').parent().css('background','#ec3324');
		if(jQuery('#fib_correct').length > 0) {
			fib_check ();
		}
		if(jQuery('.actual_word').length > 0) {
			match_word_check ();
		}
		jumble_drag ();
		jQuery('.answer_link .descs').show();
		jQuery('.answer_link .descs p').show();
		jQuery('.answer_link p').click(function() {
			jQuery('.answer_link .ans_desc').show();
		});
		jQuery('.ans_desc .cl').click(function () {
    	jQuery('.answer_link').css('display','none');
		});
		jQuery('.button-option .input_class').attr('disabled','disabled');
		/*
		//newcode
		 jQuery( '.answer-option li' ).draggable({ disabled: true });
		 */
		jQuery('.btn-wrap-inner').hide();
		random_img ();
		if(jQuery('.clicker').length > 0){
			auto_add_excel();
		}
	});
}

// Jumble Question Type
function jumble_check () {
	var ans_li = jQuery('.jumble_question_wrap li').size();
	var drag_li =	jQuery('.drag-area li').size();
	var btn_html = jQuery('.btn-wrap').html();
	if (ans_li === drag_li) {
		jQuery('.desc_wrap .btn-wrap').show();
		jQuery('.desc_wrap .btn-wrap *').show();
		jQuery('.desc_wrap .btn-wrap .btn-wrap-inner').show();
		}
}

function jumble_drag () {
	var default_txt = jQuery('#option-list .drag-area.jumbd .drag').text();
	var a = default_txt.toLowerCase().replace(/\s/g, "");
	var user_enter = jQuery('#option-list .drag-area.jumbd .current_entry').text();
	var b = user_enter.toLowerCase().replace(/\s/g, "");
	if (a != b) {
		jQuery('#option-list.jumble_div .jumble_answer_input .default_box #dragtxt').append('Wrong');
		jQuery('#option-list.jumble_div .current_entry').css('border-color','#ec3324');
		jQuery('#option-list.jumble_div .current_entry').text(jQuery('textarea.drag').val());
		jQuery('.desc_wrap.jumb').addClass('sad');
		a= jQuery('.jumble .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
		b = +a + +0;
		jQuery('.jumble .exc-box .num').empty().append(b);
		jQuery('#edit-next').show();
		jQuery('.tsq-next-callback').show();
	}
	if (a === b) {
		jQuery('#option-list.jumble_div .jumble_answer_input .default_box #dragtxt').append('Correct');
		jQuery('#option-list.jumble_div .current_entry').css('border-color','#73C200');

		a= jQuery('.jumble .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
		b = +a + +1;
		jQuery('.jumble .exc-box .num').empty().append(b);
		jQuery('#edit-next').show();
		jQuery('.tsq-next-callback').show();
	}
	jumble_ans_increment ();
	jQuery('.jumb .btn-wrap-inner').hide();
}

// Match the following content
function match_display () {
	var check_drag = jQuery('.col2 .box-area');
	var count_li = jQuery('#option-list-match .answer-option ul').size();
	var yesorno = 0;
	jQuery('.box-area').each(function(){
		 var value = jQuery(this).text();
			if(value != '') {
				yesorno++;
			}
	});
	if(yesorno == count_li) {
		jQuery('.desc_wrap .btn-wrap ').show();
		jQuery('.desc_wrap .btn-wrap *').show();
	}
}

function match_individual_check(){
	var yesorno = 0;
	jQuery('.drag-area.col2').each(function(){
		 val1 = jQuery(this).find('.j_word').text().toLowerCase().replace(/\s/g, "");
		 val2 = jQuery(this).find('.correct_match').text().toLowerCase().replace(/\s/g, "");
		 match_img1 = jQuery(this).find('.j_word img').attr('src');
		 match_img2 = jQuery(this).find('.correct_match img').attr('src');
		if(match_img1 == match_img2) {
			jQuery(this).css('background','#73C200');
			yesorno++;
		}
		else {
			jQuery(this).css('background','#ec3324');
			yesorno++;
		}
		if(val1 == val2) {
			jQuery(this).css('background','#73C200');
			yesorno++;
		}
		else {
			jQuery(this).css('background','#ec3324');
			yesorno++;
		}
	});
}

function match_word_check () {
	val1 = jQuery('.col2 ol.box-area').text().toLowerCase().replace(/\s/g, "")  ;
	val2 = jQuery('.actual_word').text().toLowerCase().replace(/\s/g, "")  ;
	match_correct_txt = jQuery('.input_match');
	if(val1 === val2) {
		jQuery('#option-list-match .main_qs_area  #dragtxt').append('Correct');
			a= jQuery('.match_the_following .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
			b = +a + +1;
			jQuery('.match_the_following .exc-box .num').empty().append(b);
	}
	else {
			jQuery('#option-list-match .main_qs_area .default_box #dragtxt').append('Wrong');
			jQuery('.desc_wrap.match').addClass('sad');
			a= jQuery('.match_the_following .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
			b = +a + +0;
			jQuery('.match_the_following .exc-box .num').empty().append(b);
	}
	match_ans_increment ();
}



// Drag and Drop JS code
function drag_drop() {
	jQuery('.answer-option li').live('mouseover',function(){
   var match = jQuery('.col1').text();
		jQuery( '.answer-option li' ).draggable({
		live: true,
		appendTo: "body",
		helper: "clone"
		});
		jQuery( '.drag-area ol' ).droppable({
		activeClass: "ui-state-default",
		hoverClass: "ui-state-hover",
		accept: ":not(.ui-sortable-helper)",
		 live: true,
		drop: function( event, ui ) {
			if(match) {
				if(jQuery(this).html().trim()) {
					return false;
				}
			}
			jQuery( '<li class="j_word"></li>' ).html( ui.draggable.html() ).appendTo(this);

//@newcode
			ui.draggable.hide();

			var box_value = jQuery('ol.box-area').text();
			jQuery('.current').text(box_value);
			jumble_check();
			match_display();
			}
		});
		jQuery( '.answer-option li' ).draggable({
    		drag: function(event, ui) {
        	// Add .dragClass when li has been dragged
        	$(this).addClass('dragClass');
    		}
		});
		/*
		newcode

		jQuery('.answer-option li.dragClass').draggable({ disabled: true });
		*/
	});
}

// Fill in the blank question

/* Function for focusing input box by default */
function fibkeypress() {
	jQuery('#fib_expected .userenter:first').focus();
	jQuery('.userenter').live('keyup', function(e){
		if(jQuery(this).val().length==jQuery(this).attr('maxlength')) {
				jQuery(this).next(':input').focus();
		}
		var txtData = [];
		jQuery('.userenter').each(function () {
			txtData.push(jQuery(this).val());
		});
		jQuery(".mergeval").val(txtData.join(''));
		jQuery('.mergeval').html(jQuery(".mergeval").val());
	});
}

/*Function for show yes and no button when all inpput box filled*/
function fib_buttons () {
	jQuery('#fib_expected input').live('keyup change',function (){
	var count_fib_input = jQuery('#fib_expected input').size();
	var i = 0;

		jQuery('.userenter').each(function(){
			var valfib = jQuery(this).val();
			if(valfib != '') {
					i++;
			}
		});
		if(i == count_fib_input) {
			//jQuery('.desc_wrap fib').show();
			jQuery('.desc_wrap .btn-wrap').show();
			jQuery('.desc_wrap .btn-wrap *').show();
		}
	});
}

/*Function for check correct and wrong answer in fib*/
function fib_check () {
		var a = jQuery('.mergeval').text().toLowerCase().replace(/\s/g, "")  ;
		var c = jQuery('#fib_correct').val().toLowerCase().replace(/\s/g, "")  ;
		var d = jQuery('#fib_correct').val();
		if ( a == c ) {
			jQuery('#fib_expected').css({'background':'#73C200','color':'#fff'});
			jQuery('#fib_expected .userenter').css('color','#fff');
			jQuery('.fib_area').empty();
			jQuery('.fib_area').append('<b>'+ d +'</b>');
			jQuery('#fib.give_val').append('Correct');
			jQuery('#fib.give_val').attr('value', 'Correct');
			a= jQuery('.fib_quest .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
			b = +a + +1;
			jQuery('.fib_quest .exc-box .num').empty().append(b);
			ans_fib_txt = jQuery('#fib.give_val').text().replace(/\s/g, "")  ;
			if ( ans_fib_txt === 'Correct'){
				aa = jQuery('.fib .correct-ans').text(); // Add +1 to correct answer when clicking on are you sure button
				bb = +aa + +1;
				jQuery('.fib .correct-ans').empty().append(bb);
			}
		}else{
			jQuery('#fib_expected').css({'background':'#EC3324','color':'#fff'});
			jQuery('.desc_wrap.fib').addClass('sad');
			jQuery('#fib_expected .userenter').css('color','#fff');
			jQuery('.fib_area').empty();
			jQuery('.fib_area').append('<b>'+ d +'</b>');
			jQuery('#fib.give_val').append('Wrong');
			jQuery('#fib.give_val').attr('value', 'Wrong');

			a= jQuery('.fib_quest .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
			b = +a + +0;
			jQuery('.fib_quest .exc-box .num').empty().append(b);
			ans_fib_txt = jQuery('#fib.give_val').text().replace(/\s/g, "")  ;
			if ( ans_fib_txt === 'Wrong'){
				aa = jQuery('.fib .wrong-ans').text(); // Add -1 to wrong answer when clicking on are you sure button
				bb = +aa + +1;
				jQuery('.fib .wrong-ans').empty().append(bb);
			}
		}
		jQuery('.userenter').attr('disabled','disabled');
		jQuery('.fib .btn-wrap-inner').hide();
}

// Random Text Show on submit
function random_img (){
	final_val  = jQuery('.give_val').val();
	if (final_val == "") {
		final_val  = jQuery('.give_val').text();
	};
	jQuery('.desc_wrap .btn-wrap').append(randomcust(final_val));
	//setTimeout("jQuery('.final_txt').remove()", 2000);
}
// Random Text Genration
var correct_stat = new Array();
correct_stat[0] = "Good job";
correct_stat[1] = "Well done";
correct_stat[2] = "That's it";
correct_stat[3] = "Fantastic";
var wrong_stat = new Array();
wrong_stat[0] = "Not really,let's try another one";
wrong_stat[1] = "That was tough, try another one";
wrong_stat[2] = "Oops! Let's go to the next one";
wrong_stat[3] = "Aw!Never mind! Try some more";
var txt_length = correct_stat.length;
function randomcust(stat) {
var rt ;
 var randnum = Math.floor(Math.random()*txt_length);
 if (stat == "Correct") {
   var rt = '<span class="correct">'+ correct_stat[randnum] + '</span>';
 }
 else if (stat == "Wrong"){
   var rt = '<span class="wrong">' + wrong_stat[randnum] + '</span>';
 }
 else {

 	var rt = '<span class="wrong">oops something bad happened</span>';
 }
return '<div class="final_txt">' + rt + '</div>';
}

function remove_div() {
	jQuery('#edit-next').live('click',function(){
		jQuery('.btn-wrap').removeAttr('style');
		jQuery('.final_txt').remove();
		jQuery('.btn-wrap').css('display','none');
		jQuery('.descs ').css('display','none');
	});
	jQuery('.tsq-next-callback').live('click',function(){
		jQuery('.btn-wrap').removeAttr('style');
		jQuery('.final_txt').remove();
		jQuery('.btn-wrap').css('display','none');
		jQuery('.descs ').css('display','none');
	});
}

function auto_add_excel(){
	ans_sub_txt = jQuery('.clicker').text().replace(/\s/g, "")  ;
	if (ans_sub_txt === 'Correct') {
	a= jQuery('.mcqndtf .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
	b = +a + +1;
	jQuery('.mcqndtf .exc-box .num').empty().append(b);
	aa = jQuery('.correct-ans').text(); // Add +1 to correct answer when clicking on are you sure button
	bb = +aa + +1;
	jQuery('.mcqndtf .correct-ans').empty().append(bb);
	}
	else {
	a= jQuery('.mcqndtf .exc-box .num').text(); // Add +1 to excellonze when clicking on are you sure button
	b = +a + +0;
	jQuery('.mcqndtf .exc-box .num').empty().append(b);
	aa = jQuery('.mcqndtf .wrong-ans').text(); // Add -1 to wrong answer when clicking on are you sure button
	bb = +aa + +1;
	jQuery('.mcqndtf .wrong-ans').empty().append(bb);
	jQuery('.desc_wrap.mcqndtf').addClass('sad');
	}
	if (jQuery('#fib.give_val') === 'Correct'){
		aa = jQuery('.fib .correct-ans').text(); // Add +1 to correct answer when clicking on are you sure button
		bb = +aa + +1;
		jQuery('.fib .correct-ans').empty().append(bb);
	}
	if (jQuery('#fib.give_val') === 'Wrong'){
		aa = jQuery('.fib .wrong-ans').text(); // Add -1 to wrong answer when clicking on are you sure button
		bb = +aa + +1;
		jQuery('.fib .wrong-ans').empty().append(bb);
	}
}

function jumble_ans_increment () {
	ans_jumb_txt = jQuery('.jumble_answer_input .give_val').text().replace(/\s/g, "")  ;
	if (ans_jumb_txt == 'Correct'){
		aj = jQuery('.jumble .correct-ans').text(); // Add +1 to correct answer when clicking on are you sure button
		bj = +aj + +1;
		jQuery('.jumble .correct-ans').empty().append(bj);
	}
	else{
		aj = jQuery('.jumble .wrong-ans').text(); // Add +1 to correct answer when clicking on are you sure button
		bj = +aj + +1;
		jQuery('.jumble .wrong-ans').empty().append(bj);
	}
}

function match_ans_increment () {
	ans_match_txt = jQuery('#option-list-match .main_qs_area  #dragtxt').text().replace(/\s/g, "")  ;
	if (ans_match_txt == 'Correct'){
		aj = jQuery('.match_the_following .correct-ans').text(); // Add +1 to correct answer when clicking on are you sure button
		bj = +aj + +1;
		jQuery('.match_the_following .correct-ans').empty().append(bj);
	}
	else{
		aj = jQuery('.match_the_following .wrong-ans').text(); // Add +1 to correct answer when clicking on are you sure button
		bj = +aj + +1;
		jQuery('.match_the_following .wrong-ans').empty().append(bj);
	}
}

function auto_height (){
  a = jQuery('#golive-form .right_exl_block').height();
  b = jQuery('#golive-form .golive_live_update').height();
  c = +a + +b;
  d = c + 70;
  jQuery('#golive-form #edit-next').css('top', d);
}

function level_change_txt(msg){

	if(msg != 'not_started') {
    jQuery('#assessments-form .assessment-header').append('<div class="oness">'+msg+'</div>');
		//setTimeout("jQuery('.testdiv').remove()", 8000);
		//}
  	//setTimeout("jQuery('.one').remove()", 2000);
	}
	else {
		jQuery('#assessments-form .assessment-header').append('');
		jQuery('.oness').remove();
		jQuery('.testdiv').remove();
	}
}


