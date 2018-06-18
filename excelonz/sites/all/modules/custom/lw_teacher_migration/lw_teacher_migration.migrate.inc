<?php

/**
 * @file
 * Migration classes for migrating users and profiles
 *
 * based on: drupal.org/node/1269066#comment-4988994
 * and:      drupal.org/node/1190958#comment-4616032
 */

/**
 * Abstract class as a base for all our migration classes
 */
abstract class lw_Migration extends Migration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct(MigrateGroup::getInstance('lwtMigrate'));
    // Avoid known line ending issue: drupal.org/node/1705850
  //  ini_set('auto_detect_line_endings', TRUE);
  }
}

/**
 * User-only migration - not profile fields
 *
 * Data files are assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class lw_Step1_TeacherMigration extends lw_Migration {
  public function __construct() {
    parent::__construct();
      $teacher_csv = variable_get('migration_teacher_csv_file');
      $file_path =  'sites/default/files/teacher_csv/'.$teacher_csv;
    $this->description = t('Import an CSV-file (only "Account"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')), 
      2 => array('name', t('Member-ID (must be unique)')),
      3 => array('field_first_name', t('First Name (Account)')),
      4 => array('field_last_name', t('Last Name (Account)')),
      5 => array('password', t('Password (Account)')),
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . $file_path , $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    // Mapped fields

 $this->addFieldMapping('mail', 'mail')
     // ->defaultValue('')
      ->description(t('Email address'));
    $this->addFieldMapping('init')
      ->defaultValue('')
      ->description(t('Email address used for initial account creation'));

      $this->addFieldMapping('name', 'name')->dedupe('users', 'name');
  
    $this->addFieldMapping('pass', 'password')
      ->defaultValue('asdf')
      ->description(t("User's password (plain text)"));
    $this->addFieldMapping('is_new')
      ->defaultValue(TRUE)
      ->description(t('Build the new user (0|1)'));
    //first name
    $this->addFieldMapping('field_first_name', 'field_first_name')
      ->defaultValue('')
      ->description(t('First name'));
    $this->addFieldMapping('field_last_name', 'field_last_name')
      ->defaultValue('')
      ->description(t('Last name'));
    $this->addFieldMapping('roles')
      ->defaultValue(7)
      ->description(DRUPAL_AUTHENTICATED_RID . t(' = "authenticated user"'));
    $this->addFieldMapping('theme')
      ->defaultValue('')
      ->description(t("User's default theme"));
    $this->addFieldMapping('signature')
      ->defaultValue('')
      ->description(t("User's signature"));
    $this->addFieldMapping('signature_format')
      ->defaultValue('filtered_html')
      ->description(t('Which filter applies to this signature'));
    $this->addFieldMapping('created')
      ->defaultValue(time())
      ->description(t('UNIX timestamp of user creation date'));
    $this->addFieldMapping('access')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for previous time user accessed the site'));
    $this->addFieldMapping('login')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for user\'s last login'));
    $this->addFieldMapping('status')
      ->defaultValue(1)
      ->description(t('Whether the user is active(1) or blocked(0)'));
    $this->addFieldMapping('timezone')
      ->defaultValue(t('Europe/London')) // 'America/Los_Angeles', 'Europe/Berlin', 'UTC', ... from drupal.org/node/714214
      ->description(t("User's time zone"));
    $this->addFieldMapping('language')
      ->defaultValue(t('en')) // e.g.: 'en', 'fr', 'de', ...
      ->description(t("User's default language"));
    $this->addFieldMapping('picture')
      ->defaultValue(0)
      ->description(t('Avatar of the user'));

    // Other handlers
    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->defaultValue(NULL)
           ->description(t('Path alias'));
    }
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('role_names', 'data'));
  }

}



/**
 * Profile2 field migration
 *
 * Data files are assumed to be in
 *   sites/all/modules/a_wusel_migration/data_sources/
 */
class lw_Step2_TeacherMigration extends lw_Migration {
public function __construct() {
    parent::__construct();
    global $user;
    $teacher_csv = variable_get('migration_teacher_csv_file');
    $file_path =  'sites/default/files/teacher_csv/'.$teacher_csv;
    $this->description = t('Import an CSV-file with Profile2-fields ("s"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Member-ID (must be unique)')),
      3 => array('field_first_name', t('First Name (Account)')),
      4 => array('field_last_name', t('Last Name (Account)')),
      5 => array('password', t('Password (Account)')),
 //     6 => array('field_class1', t('class name (for Memberlist)')),
   //   7 => array('field_subjects', t('Subject and Topics (for Memberlist)')),
      6 => array('field_collection_of_class', t('Add multi class(for Memberlist)')),
      7 => array('field_collection_of_subject', t('Add multi subject (for Memberlist)')),
      8 => array('field_teacher_school_identifier', t('School identifier (for Memberlist)')),
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' .$file_path , $columns, array('header_rows' => 1));
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('lw_Step1_Teacher');
    $this->destination = new MigrateDestinationProfile2('teacher_profile');  // 'memberlist' is the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    // Connecting the profile2 to the user:
    $this->addFieldMapping('uid', 'MID')
         ->sourceMigration('lw_Step1_Teacher')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));

    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));

    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));

        //first name
    $this->addFieldMapping('field_first_name', 'field_first_name')
      ->defaultValue('')
      ->description(t('First name'));
    $this->addFieldMapping('field_last_name', 'field_last_name')
      ->defaultValue('')
      ->description(t('Last name'));
    $this->addFieldMapping('field_name:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
    //user class
    // $this->addFieldMapping('field_class1', 'field_class1')
    //   ->defaultValue('')
    //   ->arguments(array('source_type' => 'tid'))
    //   ->callbacks(array($this, 'class_split'))
    //   ->description(t('The class name for the user'));
    //field_subjects
    // $this->addFieldMapping('field_subjects', 'field_subjects')
    //   ->defaultValue('')
    //   ->arguments(array('source_type' => 'tid'))
    //   ->callbacks(array($this, 'subject_split'))
    //   ->description(t('The subject name for the user'));
      //field_schools
       $this->addFieldMapping('field_schools', 'field_teacher_school_identifier')
      ->defaultValue('')
     // ->arguments(array('source_type' => 'tid'))
      ->callbacks(array($this, 'teacher_school_name'))
      ->description(t('The school name for the user'));
     
     //school_branch
       $this->addFieldMapping('field_branch', 'field_teacher_school_identifier')
      ->defaultValue('')
     // ->arguments(array('source_type' => 'tid'))
      ->callbacks(array($this, 'teacher_school_branch'))
      ->description(t('The branch (for Memberlist)'));
     
      //field_identifier
    $this->addFieldMapping('field_teacher_school_identifier', 'field_teacher_school_identifier')
      ->defaultValue('')
     // ->arguments(array('source_type' => 'tid'))
      ->callbacks(array($this, 'teacher_school_identifier'))
      ->description(t('The school identifier'));
    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));

    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }

 //  public function class_split($data) {
 //    // enable empty (= unknown) birthday-string:
 //      $ex_d = explode(",", $data);
 //      $opt = array();
 //      $main_data = array();
 // foreach ($ex_d as $data1) {
 //    $ex_data = explode("-", $data1);
 //    $class_name = $ex_data[0];
 //    $class_section = $ex_data[1];
    
 //    $term_find_query = db_select('taxonomy_term_data', 'td')
 //      ->fields("td", array('tid'))
 //      ->condition("vid", 2)
 //      ->condition("name", $class_name)
 //      ->range(0, 1)
 //      ->execute()->fetchAll();
 //    $class_tid = $term_find_query[0]->tid;

 //    $term_find_query = db_select('taxonomy_term_data', 'td');
 //      $term_find_query->join("taxonomy_term_hierarchy", "th", "td.tid = th.tid and th.parent =" . $class_tid);
 //      $term_find_query->fields('td', array("tid"))
 //        ->condition("vid", 2)
 //        ->condition("name", $class_section);
 //    $term_find_query_res = $term_find_query->execute()->fetchAll();
 //    $class_sec = $term_find_query_res[0]->tid;

 //   //  $main_data[$class_tid] = $class_sec;
 //     $class_sec_arr[] =  $class_sec;
 //     $class_tid_arr[] =  $class_tid;
 //     $output = array_unique( array_merge( $class_sec_arr , $class_tid_arr));

 // }
 //  return $output;


 //  }
//   public function subject_split($data) {
//     // enable empty (= unknown) birthday-string:

//     $ex_d = explode(",", $data);
//     $opt = array();
//     foreach ($ex_d as $data1) {
    
      
//       $ex_data = explode("-", $data1);
//       $class_name = $ex_data[0];
//       $class_subject = $ex_data[1];
//       if($class_subject == "GK") 
//         $class_subject = "General Knowledge";
    
//       $query = db_select('taxonomy_term_data', 'fs');
//       $query->fields('fs',array('tid',));
//       $query->condition('name', $class_name);
//       $query->range(0, 1);
//       $result = $query->execute()->fetchAssoc();
//       $subject_tid = $result['tid'];

//       $term_find_query = db_select('taxonomy_term_data', 'td');
//         $term_find_query->join("taxonomy_term_hierarchy", "th", "td.tid = th.tid and th.parent =" . $subject_tid);
//         $term_find_query->fields('td', array("tid"))
//           ->condition("vid", 7)
//           ->condition("name", $class_subject);
//         $term_find_query_res = $term_find_query->execute()->fetchAll();
//       $class_subject_tid = $term_find_query_res[0]->tid;

//       $opt[] = $class_subject_tid;
//     }
//   return $opt;
// }
  public function teacher_school_identifier($data) {
            $query = db_select('node', 'n');
              $query->fields('n',array('Nid',));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
        $result = $query->execute()->fetchAssoc();
        $nid = $result['Nid'];
  return $nid;
}
 public function teacher_school_name($data) {
          $query = db_select('node', 'n');
              $query->INNERJOIN("field_data_field_school_name", "fsname", "fsname.entity_id = n.nid");
              $query->INNERJOIN("taxonomy_term_data", "ttd", "ttd.tid = fsname.field_school_name_tid");
              $query->fields("ttd", array("name"));
              $query->fields('n',array('Nid'));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
              $result = $query->execute()->fetchAssoc();
              $school_name = $result['name'];
  
  return $school_name;
}   

public function teacher_school_branch($data) {
            $query = db_select('node', 'n');
              $query->INNERJOIN("field_data_field_school_branch", "fsbranch", "fsbranch.entity_id = n.nid");
              $query->INNERJOIN("taxonomy_term_data", "ttd", "ttd.tid = fsbranch.field_school_branch_tid");
              $query->fields("ttd", array("name"));
              $query->fields('n',array('Nid'));
              $query->condition('title', $data);
              $query->condition('type', 'partner_school');
              $query->range(0, 1);
              $result = $query->execute()->fetchAssoc();
              $school_branch = $result['name'];
      return $school_branch;
    }
public function complete($entity, stdClass $source_row) {

/*
   *Submit filed collection Subject value from csv.
   */
      $UID = $entity->uid;
      $data = $source_row->field_collection_of_class;
      $ex_d = explode(",", $data);
      $main_data = array();
      $i = 0;
foreach ($ex_d as $data1) {  
    $Ex_data = explode("-", $data1);
    $Class_name = $Ex_data[0];
    $class_section = $Ex_data[1];
    $term_find_query = db_select('taxonomy_term_data', 'td')
      ->fields("td", array('tid'))
      ->condition("vid", 2)
      ->condition("name", $Class_name)
      ->range(0, 1)
      ->execute()->fetchAll();
    $class_tid = $term_find_query[0]->tid;
    $term_find_query = db_select('taxonomy_term_data', 'td');
    $term_find_query->join("taxonomy_term_hierarchy", "th", "td.tid = th.tid and th.parent =" . $class_tid);
    $term_find_query->fields('td', array("tid"))
        ->condition("vid", 2)
        ->condition("name", $class_section );
    $term_find_query_res = $term_find_query->execute()->fetchAll();
    $class_sec = $term_find_query_res[0]->tid;
 //content_migrate_unt_save_teacher_class_field_collection($class_tid, $class_sec, $UID);
  //  $mainarray[$i]
 	$mainarray[$i]['class_tid'] = $class_tid;
 	$mainarray[$i]['class_sec'] = $class_sec;
 	$i++;
   }


$i = 0;
  /*
   *Submit filed collection Subject value from csv.
   */
  $field_subjects = $source_row->field_collection_of_subject;
  $subjects_level_one = explode("#", $field_subjects);
foreach($subjects_level_one as $keys=>$values){
          $subjects_level_two = explode(",", $values);  
           unset($opts);
    foreach($subjects_level_two as $ex_two){
         $ex_data = explode("-", $ex_two);
         $class_name = $ex_data[0];
         $class_subject = $ex_data[1];
        if($class_subject == "GK") 
        $class_subject = "General Knowledge";
      $query = db_select('taxonomy_term_data', 'fs');
      $query->fields('fs',array('tid',));
      $query->condition('name', $class_name);
      $query->range(0, 1);
      $result = $query->execute()->fetchAssoc();
      $subject_tid = $result['tid'];

      $term_find_query = db_select('taxonomy_term_data', 'td');
        $term_find_query->join("taxonomy_term_hierarchy", "th", "td.tid = th.tid and th.parent =" . $subject_tid);
        $term_find_query->fields('td', array("tid"))
          ->condition("vid", 7)
          ->condition("name", $class_subject);
        $term_find_query_res = $term_find_query->execute()->fetchAll();
      $class_subject_tid = $term_find_query_res[0]->tid;

      $opts[] = $class_subject_tid;
       }
    //   content_migrate_unt_save_teacher_subject_field_collection($opts,$UID);  
       $mainarray[$i]['subjects'] = $opts;

       		$i++;
     }
     foreach($mainarray as $main) {
     	content_migrate_unt_save_teacher_class_field_collection($main,$UID);
     }

   }
}

// $Id$


/**
 * @file
 * Manage Spandan Category term Migration
 */
/**
 * Migrate Parent Category terms
 *
 */
class lw_TeacherTermMigration extends lw_Migration {
  public function __construct() {
    parent::__construct();
      $teacher_csv = variable_get('migration_teacher_csv_file');
      $file_path =  'sites/default/files/teacher_csv/'.$teacher_csv;
    $this->description = t('Category term migration');

    $columns = array(
      0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('field_first_name', t('First Name (Account)')),
      3 => array('field_last_name', t('Last Name (Account)')),
      4 => array('password', t('Password (Account)')),
     // 5 => array('field_class_user', t('class name (for Memberlist)')),
     // 6 => array('field_subjects', t('Subject and Topics (for Memberlist)')),
      5 => array('field_schools', t('school name (for Memberlist)')),
      6 => array('field_collection_of_class', t('Add multi class(for Memberlist)')),
      7 => array('field_collection_of_subject', t('Add multi subject (for Memberlist)')),
      8 => array('field_branch', t('branch (for Memberlist)')),
    );

    // TIP: delete ", array('header_rows' => 1)" in the next line, when the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' .$file_path , $columns, array('header_rows' => 1));
    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
    // class, which uses database tables for tracking. Pass the machine name
    // (BeerTerm) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.

    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'field_schools' => array('type' => 'varchar',
                        'length' => 255,
                        'not null' => TRUE,
                        'description' => 'User\'s Member-ID',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
      $this->destination = new MigrateDestinationTerm('school');

    // Assign mappings TO destination fields FROM source fields. To discover
    // the names used in these calls, use the drush commands
    // drush migrate-fields-destination BeerTerm
    // drush migrate-fields-source BeerTerm
      $this->addFieldMapping('name', 'field_schools');
      $this->addFieldMapping('description', 'CLASS_CODE')->defaultValue('');
      $this->addFieldMapping('weight')
           ->defaultValue('0');

  // un-mapped field
    $this->addFieldMapping('format')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('field_schools')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'));
  }
    public function prepare(stdClass $account, stdClass $row) {

    }
}

class lw_TeacherBranchMigration extends lw_Migration {
  public function __construct() {
    parent::__construct();
      $teacher_csv = variable_get('migration_teacher_csv_file');
      $file_path =  'sites/default/files/teacher_csv/'.$teacher_csv;
    $this->description = t('Category term migration');

    $columns = array(
         0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')),
    //  2 => array('name', t('Name (Account)')),
      2 => array('field_first_name', t('First Name (Account)')),
      //4 => array('field_middle_name', t('middle Name (Account)')),
      3 => array('field_last_name', t('Last Name (Account)')),
      4 => array('password', t('Password (Account)')),
      //5 => array('field_class_user', t('class name (for Memberlist)')),
      //6 => array('field_subjects', t('Subject and Topics (for Memberlist)')),
      5 => array('field_schools', t('school name (for Memberlist)')),
      6 => array('field_collection_of_class', t('Add multi class(for Memberlist)')),
      7 => array('field_collection_of_subject', t('Add multi subject (for Memberlist)')),
      8 => array('field_branch', t('branch (for Memberlist)')),
    );

    // TIP: delete ", array('header_rows' => 1)" in the next line, when the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . $file_path , $columns, array('header_rows' => 1));
    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
    // class, which uses database tables for tracking. Pass the machine name
    // (BeerTerm) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.

    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'field_branch' => array('type' => 'varchar',
                        'length' => 255,
                        'not null' => TRUE,
                        'description' => 'User\'s Member-ID',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
      $this->destination = new MigrateDestinationTerm('branch');

    // Assign mappings TO destination fields FROM source fields. To discover
    // the names used in these calls, use the drush commands
    // drush migrate-fields-destination BeerTerm
    // drush migrate-fields-source BeerTerm
      $this->addFieldMapping('name', 'field_branch');
      $this->addFieldMapping('description', 'CLASS_CODE')->defaultValue('');
      $this->addFieldMapping('weight')
           ->defaultValue('0');

  // un-mapped field
    $this->addFieldMapping('format')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('field_branch')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'));
  }
    public function prepare(stdClass $account, stdClass $row) {
        //print_r($row);
        //print_r($account);
    }
}



