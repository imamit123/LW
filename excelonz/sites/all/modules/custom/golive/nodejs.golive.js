/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

Drupal.Nodejs.callbacks.golive_update = {
  callback: function (message) {
    if (message.callback == 'golive_update') {

      div_user_id = ".uid_" + message.data.user_id;
      correct_ans = message.data.correct;
      wrong_ans = message.data.wrong;
      true_false = message.data.ans_status;

      //alert(div_user_id);
      total = wrong_ans + correct_ans;
      ot_ans = correct_ans +'/'+ total
      jQuery('.false_col .wrong_total', div_user_id).text(wrong_ans);
      jQuery('.true_col .correct_total', div_user_id).text(correct_ans);
      jQuery('.correct_total', div_user_id).text(ot_ans + ' Correct');

      fal = jQuery('.false_col', div_user_id).children("span").length;
      tru = jQuery('.true_col', div_user_id).children("span").length;
      if(fal == wrong_ans && correct_ans == tru) {
        change_total(true_false);
      }
      else {
        jQuery('.false_col', div_user_id).html("");
        jQuery('.true_col', div_user_id).html("");

        for (var i = 0; i < wrong_ans; i++) {
          change_total("false_col");
        }
        for (var i = 0; i < correct_ans; i++) {
          change_total("true_col");
        }
      }
    }
  }
};

function change_total(res_stat) {
if (res_stat == "false_col") {
       jQuery('.false_col', div_user_id).append('<span>&nbsp;</span>');
      }
      else {
        jQuery('.true_col', div_user_id).append('<span>&nbsp;</span>');
      }
}


/**
 * will be called when nodejs is started.
 * @type {Object}
 */
Drupal.Nodejs.callbacks.golive_started = {
  callback: function (message) {

    if (message.callback == 'golive_started') {
      nid = message.data.nid;
        var l = window.location;
        var base_url = l.protocol + "//" + l.host + "/" + l.pathname.split('/')[0];

      if(location.href.match("golive-dash")) {

        //alert("golive-dash");
        jQuery('#show-on-time'+nid).text('Join');
        jQuery('#show-on-time'+nid).attr('href', base_url + 'golive/take/'+nid);
      }
      else {
        jQuery('.play-label-title').show();
        jQuery('.play-label-title a').attr('href', base_url+ 'golive/take/'+nid);
      }

    }b
  }
};

/**
 *called from golive_node_insert().
*/
Drupal.Nodejs.callbacks.golive_notify = {
  callback: function (message) {

    if (message.callback == 'golive_notify') {
        nid = message.data.nid;
        title = message.data.title;
        user_name = message.data.user_name;

      jQuery('.notify_acc_rej').append('<div class="input_wrapper"><fieldset id="edit-acc-re-fieldset'+nid+'" class="form-wrapper"><legend><span class="fieldset-legend">'+user_name +' has challenged you for '+title+'</span></legend><div class="fieldset-wrapper"></div></fieldset><input onClick="notification_nodejs_event('+nid+',0)" type="submit" class="form-submit" value="accept" name="'+nid+'" id="edit-accept"><input type="submit" class="form-submit" value="Reject" name="'+nid+'" id="edit-reject" onClick="notification_nodejs_event('+nid+', 1)" ></div>');
      var count = jQuery('.notify_num').text();
      count = +count+ +1;
      jQuery('.notify_num').text(count);
    }
  }
};
