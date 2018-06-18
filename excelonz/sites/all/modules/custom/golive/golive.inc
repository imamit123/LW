<?php

/**
 * @file
 */

/**
 * Called from hook_menu for golive page.
 */
function golive_get_page() {
  global $base_url, $user;
  $uid = $user->uid;
  $output = '';

  //drupal_add_js( drupal_get_path('module', 'golive') . '/go_live.js');
  //set timezone somewhere else.
  date_default_timezone_set('Asia/Kolkata');

  //Link to craete a go live session
  $create_url = $base_url . '/node/add/go-live';
  $output = '<div class="golive-create"><a href="' . $create_url . '">CREATE GO LIVE</a></div>';
  //$output .= '<div class="golive_timer"><div class="coconut seconds big" alt="51"><div class="count"></div><div class="color" style="top: 59px; left: 59px;"></div><canvas height="128" width="128" class="canvas" id="canvas"></canvas><div id="countdown" class="center" style="color: rgb(90, 25, 37);"></div></div>';


//  echo time() . "<br/>";
//  echo date("d - G - i - s");
  //Fetch upcoming go live details.
  // Using Db select as entityfieldquery would create problem with join
  $query = db_query("select cl.entity_id, field_time_value
    from
      field_data_field_user_status cl,
      field_data_field_users usr,
      field_data_field_request_status st,
      field_revision_field_time tm
    WHERE
      cl.field_user_status_value = usr.entity_id
    AND
      cl.field_user_status_value = st.entity_id
    AND
      cl.entity_id = tm.entity_id
    AND
     unix_timestamp(concat(field_time_value, 'GMT+5.5')) > (unix_timestamp() + 10800)
    AND
     field_users_uid = ".$uid."
    AND
      field_request_status_value = :status
    ORDER BY unix_timestamp(field_time_value) ASC
    LIMIT 10",
    array(':status' => "Approved"));
  $result = $query->fetchAll();
  $nid = $result[0]->entity_id;
  //@todo : author's nide will not come here so need to add it as well.

  //echo "<pre>"; print_r($result);
  //foreach($result as $row) {
  //  echo $row->entity_id;
  //}
  $node_info = node_load($nid);



  //check for logged in user is owner of this node then show start button.
  //else join button for other user when golive started.
  $start_ready = '<FORM METHOD="LINK" ACTION="/golive/take/' . $nid . '">';
  if ($node_info->uid == $uid) {
    //show start button when time come
    $start_ready .= "<input id='start-button' type='submit' class='session_button' value='start' disabled='disabled'>";
  }
  else{
  $start_ready .= "<p class='join_txt' style='display:none;'><b>Waiting for Organiser to Start</b></p>";
    $start_ready .= "<input id='join-button' type = 'submit' class='session_button' value='join'>";
  }
  $start_ready .= '</FORM>';


  //fetch required field
  $author_name = $node_info->name;
  $topic_tid = $node_info->field_go_live_subject['und'][0]['tid'];
  $topic_info = taxonomy_term_load($topic_tid);
  $topic_name = $topic_info->name;
  $subject_info = taxonomy_get_parents($topic_tid);
  $key = array_keys($subject_info);
  $subject_name = $subject_info[$key[0]]->name;
  $time = $node_info->field_time['und'][0]['value'];
  $users_list = array();
  foreach ($node_info->field_user_status['und'] as $row) {
    $user_info = entity_load_single('field_collection_item', $row['value']);
    if ($user_info->field_request_status['und'][0]['value'] == "Approved" ) {
      $users_list[] = $user_info->field_users['und'][0]['uid'];
    }
  }

  //Display data.
  $user_output = '';
  foreach ($users_list as $user_id) {
    $user_participant = user_load($user_id);
    $user_output .= "<img src = 'sites/default/files/styles/thumbnail/public/pictures/".$user_participant->picture->filename."' />";
    $user_output .= "<br/> Name = " . $user_participant->name;
  }

  $title = $node_info->name . "'s go live in " . $subject_name . " on " . $topic_name . " at " . $time . "<br/>";
  $output .= $title . $user_output . $start_ready;

  $output .= "<br>" . $nid;

  $output .= "<br/>Remaining Time : " . elapsed_time(strtotime($result[0]->field_time_value) - time());
  $output .= '<br/>' . (strtotime($result[0]->field_time_value) - time());
  $output .= '<div id="remain_id"></div>';


  //pass time in js to show start buttons
  drupal_add_js(array(
    'golive_rem_time' => array(
      'rem_time' =>  (strtotime($result[0]->field_time_value) - time()),
    ),
  ),
  'setting');

  //var datainput1 = Drupal.settings.golive_rem_time.rem_time;
  return $output;
}


/**
 *  Function to generate the form.
 *  This function will call for the first time when golive is started.
 *  Steps
 *    - Identify node and store it in session.
 *    - Fetch first question from node.
 *    - Generate form with first question.
 *    - Place a button for submit.
 *    - save users score
 *    - fetch next question.
 *    - fetch question till time end.
 *    - show results.
 */
function golive_form($form, &$form_state) {
  drupal_add_js( drupal_get_path('module', 'golive') . '/nodejs.golive.js');
  drupal_add_js('http://code.jquery.com/jquery-1.4.4.min.js'); // prateek
  drupal_add_js('http://code.jquery.com/jquery-1.7.2.min.js'); // prateek
  drupal_add_js('http://code.jquery.com/ui/1.8.21/jquery-ui.min.js'); // prateek
  //@todo : move js to the type where it is required.
  drupal_add_js( drupal_get_path('module', 'assessments') . '/assessments.js');
  drupal_add_css( drupal_get_path('module', 'assessments') . '/assessments.css');
  drupal_add_js( drupal_get_path('module', 'assessments') . '/jquery.ui.touch-punch.min.js');// prateek

  global $user;
  //@todo : check the golive is exist or live or expire.
  $nid = arg(2);
  if (!is_numeric($nid)) {
    //@todo :  return with error message
  }



  if ($_SESSION['golive']['nid'] != $nid) {
      unset($_SESSION['golive']);
  }


  /*//if user is coming from any other session running then redirect user.
    if(array_key_exists('golive', $_SESSION) && ($_SESSION['golive']['nid'] != drupal_goto)) {
    $nid('golive/take/' . $_SESSION['golive']['nid']);
  }
  */


  //check golive status.
  $query = db_select('field_data_field_status', 'st');
    $query->join('field_data_field_started_timestamp', 'ts', 'st.entity_id = ts.entity_id'); //JOIN node with users
    $query->fields('st',array('field_status_value'));
    $query->fields('ts',array('field_started_timestamp_value'));
    $query->condition('st.entity_id', $nid,'=');
  $result = $query->execute()->fetchAssoc();

  $endtime = '';
  $holdtime = 0;
  if($result['field_status_value'] == 'waiting' && $result['field_started_timestamp_value'] == "0") {

    //first time started
    db_query("update  field_data_field_status st,
      field_data_field_started_timestamp ts
      set
        field_status_value = 'started',
        field_started_timestamp_value = '".time()."'
      where
        st.entity_id = ". $nid ." and
        ts.entity_id = st.entity_id");


    //call other users using nodejs
    $query = db_select('field_data_field_users', 'ur');
    $query->join('field_data_field_user_status', 'us', 'ur.entity_id = us.field_user_status_value'); //JOIN node with users
    $query->fields('ur',array('field_users_uid',));
    $query->condition('us.entity_id', $nid,'=');
    $result = $query->execute();
    while($record = $result->fetchAssoc()) {
  //    echo $record['field_users_uid'] . "<br/>";
    // $record['field_users_uid'];

      $message = (object) array(
     'data' => (object) array(
       'nid' => $nid,
     ),
     'channel' => 'nodejs_user_' . $record['field_users_uid'],
     'broadcast' => false,
     'callback' => 'golive_started',
    );
    Nodejs::enqueueMessage($message);
    }
    //nodejs over


    $holdtime = 30;
    $start_time = time();
  }
  else {
   //echo "second<br/>";

    $start_time = (int)$result['field_started_timestamp_value'];
   // echo "start time " . date("Y-m-d",$start_time) . "<br/>";
    //echo "start time 2= ". $start_time . "<br/>";

    $future_time = strtotime("+30 seconds", $start_time);
    if ($future_time > time()) {
      $holdtime = $future_time - time();
  //    echo "hold time " . date("Y-m-d",$holdtime) . "<br/>";
    }

    // Check for time over.
    $ses_time = strtotime("+930 seconds", $start_time);

 //   echo "session over time " . date("Y-m-d",$ses_time) . "<br/>";

    if($ses_time < time()) {
      drupal_set_message("SESSION OVER");
    }

  }
  //echo "start time" . date("r", $start_time) . "<br/>";

  //will be called for first time.
  if (!array_key_exists('golive', $_SESSION)) {

    $_SESSION['golive']['users'] = array();
    $_SESSION['golive']['nid'] = $nid;
    $_SESSION['golive']['qno'] = 0;
    $_SESSION['golive']['correct_ans'] = 0;
    $_SESSION['golive']['wrong_ans'] = 0;
    //echo '<pre>';print_r($nid);die();
    //first time fetch all other user who has accepted the event for real time notification
    $query = db_select('field_data_field_users', 'ur');
    $query->join('field_data_field_user_status', 'us', 'ur.entity_id = us.field_user_status_value'); //Join node with users
    $query->fields('ur',array('field_users_uid',));
    $query->condition('us.entity_id', $nid,'=');
    $result = $query->execute();
    while($record = $result->fetchAssoc()) {
      $_SESSION['golive']['users'][] = $record['field_users_uid'];
    }

    $result1 = db_select('node', 'n');

    $result1->fields('n', array('uid'))
      ->condition('nid', $nid,'=');
    $output = $result1->execute()
      ->fetchAssoc();
    $_SESSION['golive']['users'][] = $output['uid'];
    //$_SESSION['golive']['duration'] = $output['field_duration_value'] * 60;
    $remtime = "+" . 930 . " seconds";
    $_SESSION['golive']['duration_remaining'] = strtotime($remtime, $start_time);

//echo "duration_remaining  time " . date("Y-m-d",$_SESSION['golive']['duration_remaining']) . "<br/>";
    //check for valid user
    if (!in_array($user->uid, $_SESSION['golive']['users'])) {
      unset($_SESSION['golive']);
    }
  }

  if($holdtime > 0) {
    $remtime = 900;
  }
  else {
    $remtime = $_SESSION['golive']['duration_remaining'] - time();
  }

  //echo "remtime = " . $remtime/60 .  "<br/>";
  //echo "holdtime = " . $holdtime/60 .  "<br/>";

  //echo "duration rema = " . date("r", $_SESSION['golive']['duration_remaining']) .  "<br/>";

  //echo "rem time " . $remtime;
  //seding total duration.
  drupal_add_js(array(
    'golive_time' => array(
      'duration' => $remtime ,
      'holdtime' => $holdtime ,
     ),
    ),
  'setting');
  drupal_add_js( drupal_get_path('module', 'golive') . '/go_live_tag.js');

  //fetch the next question node id.
  $form = golive_get_question_form();

  $form['timer_value'] = array(
    '#type' => 'textfield',
    '#title' => t('timer_value'),
    '#size' => 10,
    '#maxlength' => 128,
  );
  $form['timer'] = array(
    '#type' => 'markup',
    '#markup' => '<div class= "hold">Wating For other join<br/><div id="countdown" class="center" style="color: rgb(90, 25, 37);"></div></div><div class="timer"><span class="startstoptime"><div id="countdown" class="center"></div></span></div>',
    '#weight' => -102,
  );
  $form['sure'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="btn-wrap"><div class="btn-wrap-inner"><p class="sure">Are You Sure</p>',
  );
  $form['sub'] = array(
    '#type' => 'markup',
    '#markup' => '<button id="submit-button" type="button">Yes</button>',
  );
  $form['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<button id="reset" type="button">No</button></div></div>',
  );

  $form['action']['next'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'golive_next',
      'wrapper' => array('option-list'),
      'name' => 'next',
    ),
    '#value' => t('Next'),
  );

    $topic_query = db_select('field_data_field_go_live_subject', 'e')
        ->fields('e')
        ->condition('entity_id', $nid)
        ->range(0, 1)
        ->execute()
        ->fetchAssoc();
  $topic_tid =$topic_query['field_go_live_subject_tid'];
  //fetch parent
  $subject_query = db_select('taxonomy_term_hierarchy', 'th')
    ->fields('th')
    ->condition('tid', $topic_tid)
    ->execute()->fetchAssoc();
$subject_tid = $subject_query['parent'];

  $topic = taxonomy_term_load($topic_tid);

  $parents = taxonomy_term_load($subject_tid);
  $topic_name = $topic->name;
  $subject_name = $parents->name;
  $form['head'] = array(
    '#type' => 'markup',
    '#markup' => '<div class= "assessment-header-top"><h3 class= "assessment-header">'.$subject_name." : ".$topic_name.'</h3></div><div class="assessment_wrap">',
    '#weight' => -109,
  );


    for($i = 0; $i < $_SESSION['golive']['correct_ans']; $i++) {
      $correct .= '<span>&nbsp;</span>';

    }
    for($i = 0; $i < $_SESSION['golive']['wrong_ans']; $i++) {
      $wrong .= '<span>&nbsp;</span>';
    }
    $total = $_SESSION['golive']['correct_ans'] . "/" .($_SESSION['golive']['wrong_ans'] +$_SESSION['golive']['correct_ans']);

  //loop for displaying different div for update of all users.
  //name - progress
  for ($i = 0; $i < count($_SESSION['golive']['users']); $i++) {

    $user_item = user_load($_SESSION['golive']['users'][$i]);
    //echo '<pre>';print_r($_SESSION['golive']['users'][$i]);die();
    $user_name_photo = theme('user_picture', array('account' =>$user_item)).'<b>'.get_name($_SESSION['golive']['users'][$i]). '</b>';


    if($_SESSION['golive']['users'][$i] == $user->uid) {
      $form['div' . $i] = array(
        '#type' => 'markup',
        '#markup' => '<div class = "user_online uid_' . $_SESSION['golive']['users'][$i] . '">
          <table class="user_table"><tr><td><div class = "user_name"> '. $user_name_photo.' </div></td><td><span class="correct_total">'.$total.'</span></td></tr></table>
            <div class= "user_progress">
                <span class="true_col">'.$correct.'</span>
                <span class="false_col">'.$wrong.'</span>
            </div>
          </div>',
      );
    }
      else {
        $form['div' . $i] = array(
          '#type' => 'markup',
          '#markup' => '<div class = "user_online uid_' . $_SESSION['golive']['users'][$i] . '">
          <table class="user_table"><tr><td><div class = "user_name"> '. $user_name_photo.' </div></td><td><span class="correct_total">0/0 updating..</span></td></tr></table>
            <div class= "user_progress">
                <span class="true_col"></span>
                <span class="false_col"></span>
            </div>
          </div>',
        );
      }
    if ($i ==0) {
      $form['div' . $i]['#prefix'] = "
        <div class='golive_live_update'>
          <h2>PLAY OFF! SCORES</h2>
          <div class='golive_timer'>
            <div class='coconut seconds big' alt='51'>
              <div class='count'></div>
              <div class='color'></div>
              <canvas class='canvas' id='canvas' height= '5px'></canvas>
              <div id='countdown' class='center' style='color: rgb(90, 25, 37);'>
            </div>
          </div>
        </div>";
    }
  }
  $form['div' . $i]['#suffix'] = "</div>";

  return $form;
}


/**
 * This function will call when next button will be clicked.
 */
function golive_next($form, $form_state) {
  global $user;
  //store the ans is correct or wrong
  $true_false = '';
  if ($_POST['opt'] == "Correct") {
     $_SESSION['golive']['correct_ans']++;
     $true_false = 'true_col';
  }
  else {
    $_SESSION['golive']['wrong_ans']++;
    $true_false = 'false_col';
  }


  for ($i = 0; $i < count($_SESSION['golive']['users']); $i++) {
    $message = (object) array(
     'data' => (object) array(
       'user_id' => $user->uid,
       'correct' => $_SESSION['golive']['correct_ans'],
       'wrong' => $_SESSION['golive']['wrong_ans'],
       'ans_status' => $true_false,
     ),
     'channel' => 'nodejs_user_' . $_SESSION['golive']['users'][$i],
     'broadcast' => false,
     'callback' => 'golive_update',
    );
    Nodejs::enqueueMessage($message);
  }
  $_SESSION['golive']['qno']++;
  $form1 = golive_get_question_form();

  return $form1;
}


/**
 * Function to return next question's form.
 */
function golive_get_question_form() {
  global $base_url;
  global $user;

  $exc_query = db_select('field_data_field_excellone', 'e')
    ->fields('e')
    ->condition('entity_id', $user->uid)
    ->range(0, 1)
    ->execute()
    ->fetchAll();
  $_SESSION['user_orig_exc'] = $exc_query[0]->field_excellone_value;

  //query based on nide and question no.
  $result = db_select('field_data_field_question', 'n')
    ->fields('n')
    ->condition('entity_id', $_SESSION['golive']['nid'])
    ->condition('delta', $_SESSION['golive']['qno'])
    ->execute()
    ->fetchAssoc();
  $qnid = $result['field_question_nid'];

  if(!is_numeric($qnid)) {
    $form['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list">',
      '#markup' =>  "<h1> Great Job! That was fast!<br/>
        We need to wait for your Play-off friends to finish their questions before you get to know who won this Play off!
        Meanwhile you can still see how they're doing on the progress bar</h1>" ,
      '#suffix' => '</div></div>',
    );
    return $form;
  }

  $question_info = node_load($qnid);
  //echo '<pre>';print_r($question_info);die();
  $question_type = $question_info->type;
  $name = '';
  //@todo : do not user user_load()
  $name = user_load($user->uid);
  //echo '<pre>';print_r($name);die();
  $name = $name->field_first_name['und'][0]['value'];
  $image_html = '';
  if (array_key_exists('und', $question_info->field_question_image)) {
    $quest = '';
    $img_path = '';
    $size = '';
    $img_width = '';
    $img_wrap = '';
    $img_with_txt = '';
    $img = $question_type .'/'.$question_info->field_question_image['und'][0]['filename'];
    $style = 'question_large_688_image';
    $img_path = image_style_url($style, $img);
    $size = getimagesize($img_path);
    $img_width =  $size[0];
    //$quest =  "<img src='" . $base_url . "/sites/default/files/" . $img . "' />";
    $quest =  "<img src='".$img_path."' />";
    if ($img_width < 350){
      $img_with_txt = '<div class="queston_img" style="float:left;width:'.$img_width.'">'.$quest.'</div>';
    }
    else {
      $img_with_txt = '<div class="queston_img" style="float:left;width:100%">'.$quest.'</div>';
    }
  }
  // for displaying answer description
  $ans_desc_link = '';
  if (array_key_exists('und', $question_info->field_question_description)) {
    $ans_desc = $question_info->field_question_description['und'][0]['value'];
    if ($ans_desc) {
      //$ans_desc_link = "<div class='descs'><p class='shwtxt'>View More Info</p><div class='ans_desc'><span class='cl'>X</span>" . $ans_desc . "</div></div>";
    }
  }

  $option_html = '';
  if ($question_type == "mcq") {
    foreach ($question_info->field_question_options['und'] as $option) {
      //@todo : use entity_load_single then will change $option[value] after 4 line.
     $options = entity_load("field_collection_item", array($option['value'], ));
      //echo '<pre>';print_r($options);die();
      $val = $options[$option['value']]->field_correct_answer['und'][0]['value'];
      $ans_img = $options[$option['value']]->field_image_option['und'][0]['filename'];
      if (array_key_exists('und', $options[$option['value']]->field_image_option)) {
         $img_path_mcq = '';
         $img_mcq = '';
         $img_path_mcq = '';
         $opt_img = '';
         $img_mcq = $question_type .'/'.$options[$option['value']]->field_image_option['und'][0]['filename'];
         $style_mcq = 'answer_img_mcq';
         $img_path_mcq = image_style_url($style_mcq, $img_mcq);
        if ($_SESSION['user_class_value'] > 3) {
          $opt .= "
          <div class='button-option withimg ".$question_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <img src='".$img_path_mcq."' />
              <div class='ans-bt-img'>" .$options[$option['value']]->field_option_1['und'][0]['value'] . "</div>
            </button>
          </div>";
        }
        else {
          $opt .= "
          <div class='button-option withimg ".$question_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <img src='".$img_path_mcq."' />
              <div class='ans-bt-img'>" .$options[$option['value']]->field_option_1['und'][0]['value'] . "</div>
            </button>
          </div>";
        }
      }
      else {
         if ($_SESSION['user_class_value'] > 3) {
          $opt .= "
          <div class='button-option noimg ".$question_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <div class='ans-bt'>" .$options[$option['value']]->field_option_1['und'][0]['value'] . "</div>
            </button>
          </div>";
        }
        else {
          $opt .= "
          <div class='button-option noimg ".$question_type."'>
            <button id=" . $val . " class='input_class " . $val . "' name='" . $val ."' size ='500' type='button'>
              <div class='ans-bt'>" . $options[$option['value']]->field_option_1['und'][0]['value'] . "</div>
            </button>
          </div>";
        }
      }
    }
  $opt .= "<div class='clicker'><textarea name= 'opt' class='give_val' style='display:none' ></textarea></div>";
  }

  elseif ($question_type == "true_and_false") {
    foreach ($question_info->field_answer_choices['und'] as $option) { // change in the field collection name
      $options = entity_load("field_collection_item", array($option['value'], ));
      $val = $options[$option['value']]->field_correct_answer['und'][0]['value'];
      $opt .= "
      <div class='button-option ".$question_type."'>
        <button id=" . $val . " class='input_class " . $val . "' type='button' name=" . $val . ">
          <div class='ans-bt'>" . $options[$option['value']]->field_option_1['und'][0]['value'] ."</div>
        </button>
      </div>";
    }
    $opt = $opt1 . $opt . "<div class='clicker'>
      <textarea name= 'opt' class='give_val' style='display:none' ></textarea></div>";
  }

  elseif ($question_type == 'fib') {
    $ans_desc = '';
    $question_title = '';
    $pos = '';
    $strlength = '';
    $chars = '';
    $ch1 = '';
    $ch2 = '';

    // Code for fetch word starting with special character from question text.
    $question_title = $question_info->field_question_text['und'][0]['value'];
    $pattern = '#@([^<]+)@#';
    preg_match($pattern, $question_title, $matches);
    $chars = preg_split('/ /', $matches[1], -1, PREG_SPLIT_OFFSET_CAPTURE);
    $ch1 = $chars[0][0];
    $ch2 = $chars[1][0];
    $ch3 = $chars[2][0];
    $strlength = array();
    $j = 0;
    $blank_str2 = '<span class="fib_area">';
    $blank_input2 = '';
    foreach ($chars as $key => $value) {
      $blank_str2 .= "<span class='fib_word'>";
      for($i = 0 ; $i < strlen($value[0]) ; $i ++) {
        $blank_str2 .= '_ ';
        $blank_input2 .= '<input class="userenter one in-'.$i.'" type="text" maxlength="1" autofocus="autofocus" />';
      }
      $blank_str2 .= "</span>";
      $blank_input2 .= "&nbsp;&nbsp;&nbsp;&nbsp;";
    }
    $blank_str2 .= "</span>";
    /*for($i = 0 ; $i < $strlength1 ; $i ++)
    {
      $blank_str .= '_ ';
      $blank_input .= '<input class="userenter one" type="text" maxlength="1" autofocus="autofocus" />';
    }
    for($i = 0 ; $i < $strlength2 ; $i ++)
    {
      $blank_str1 .= '_ ';
      $blank_input1 .= '<input class="userenter two" type="text" maxlength="1" autofocus="autofocus" />';
    }
    for($i = 0 ; $i < $strlength3 ; $i ++)
    {
      $blank_str2 .= '_ ';
      $blank_input2 .= '<input class="userenter three" type="text" maxlength="1" autofocus="autofocus" />';
    }
    */
    //$blank_input2 = $blank_input.'<br />'.$blank_input1.'<br />'.$blank_input2;
    //$blank_str2 = '<span class="fib_area">'.$blank_str.'&nbsp;&nbsp;'.$blank_str1 .'&nbsp;&nbsp;'.$blank_str2.'</span>';

    //Code for remove word starting with special character from question text and insert blank spaces
    //Code for remove word starting with special character from question text and insert blank spaces
    $question_title_val =  preg_replace("#@([^<]+)@#",$blank_str2, $question_title);
    $opt = '<div class="keyarea"><div id="fib_expected">'.$blank_input2.'<p class="mergeval"></p><div class="clrtxt">Clear Text</div></div><textarea id="fib_correct"  style="display:none;" >' . $matches[1] . '</textarea><textarea id="fib" name= "opt" class="give_val" style="display:none;" ></textarea></div>';
  }
  $question_title = $question_info->field_question_text['und'][0]['value'];
  $ans_store =  "<textarea name= 'opt' class='give_val' style='display:none' ></textarea>";

   $form['option'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="option-list">',
    '#markup' =>  //$question_level_print .

     '<div class="right_exl_block '.$question_type.'"><div class="session_ex2"><h2>'.$name.'<span>Earned</span></h2></div>'.
     '<div class="exc-box"><div class="wrap_bt"><span class="num">'. $_SESSION['user_orig_exc'] .'</span><br /><span>Excelonz</span></div></div>'.
    //'<br/>Session Excellonz : ' . $_SESSION['user_session_exc'] .
     $level_markup .
    //'<br/>' . $_SESSION['level_wrong_ans'] .

    '</div>'.
      '<div class="left_ex_block">
        <div id="question_area">
          <div class="question_title">
            <h2><span>Question:</span>'.$question_info->title.'</h2>
          </div>
          <div class="question-div-blk">'.$img_with_txt.
            '<div class="question-text">
              <div class="question_div">
                <h3>' . $question_info->field_question_text['und'][0]['value'] . '</h3>
              </div>
            </div>
          </div>
        </div>' .
        '<div class="hlptxt">Choose an answer below :</div>'.
        '<div class="mcq_ext_blk"><div class="question_wrap">'.$opt.'</div></div>'.
      '<div class="desc_wrap  '.$question_type.'">'.$ans_desc_link.'</div></div>',
    '#suffix' => '</div></div>',
  );

if ($question_type == 'fib') {
    $form['option'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="option-list" class="fib_quest">',
      '#markup' =>  //$question_level_print .
      '<div class="right_exl_block '.$question_type.'">
      <div class="session_ex2">
        <h2>'.$name.'<span>Earned</span></h2>
      </div>'.
     '<div class="exc-box">
      <div class="wrap_bt">
        <span class="num">'. $_SESSION['user_orig_exc'] .'</span><br /><span>Excelonz</span></div></div>'.
     $level_markup .
    '</div>'.
'<div class="left_ex_block">
        <div id="question_area">
          <div class="question_title">
            <h2><span>Question:</span>'.$question_info->title.'</h2>
          </div>
          <div class="question-div-blk">'.$img_with_txt.
            '<div class="question-text">
              <div class="question_div">
                <h3>' . $question_title_val . '</h3>
              </div>
            </div>
          </div>
        </div>' .
        '<div class="hlptxt">Fill in the blanks :</div>'.
        '<div class="fib_ext_blk"><div class="question_wrap">'.$opt.'</div></div>'.
        '<div class="fib_wrap">
          <div class="desc_wrap fib">'.$ans_desc_link.'</div>
        </div>
      </div>',
    '#suffix' => '</div></div>',
  );
  }

  return $form;
}
