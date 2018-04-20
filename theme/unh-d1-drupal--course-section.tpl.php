<div class="<?=$classes?>"<?=$attributes?>> <!-- <?=$classes?> -->
<?php 
ddl("SECTION TEMPLATE BEGIN");
ddl($variables, '$variables - template');
ddl("SECTION TEMPLATE END");

// Normally, there would be a number of themed blocks here, but we don't have the time.
// This seems to be a reasonable organization for now.  More can be done later.
// @todo: theme these better!!!

$sectionTitle = unh_d1_client_getsectionTitle($section);
$sectionNumber = unh_d1_client_getsectionCustomSectionNumber($section);
$node = node_load($course_nid);
$course_code = unh_d1_client_getcourseNumber($course);
$semester = unh_d1_client_getsectionSemester($section);
$section_title = unh_d1_client_getsectionTitle($section);

$i = $disp_idx;
$in = $disp_open;
$plus_style = ($in ? "none" : "inline");
$minus_style = ($in ? "inline" : "none");
$output = '';

// DETERMINE SECTION STATUS.
  $status = '';
  if (unh_d1_client_sectionIsWaitlisted($section)) {
    $status = '<div class="section-wait-list-status" style="5px 0 0 0">Wait List</div>';
  } elseif (unh_d1_client_sectionIsEnrollmentClosed($section)) {
    $status = '<div class="section-enrollment-closed-status" style="5px 0 0 0">Enrollment Closed</div>';
  } elseif (unh_d1_client_sectionIsFutureOffering($section)) {
    $dt = unh_d1_client_getSectionEnrollmentBeginDate($section);
    $date = $dt->format('Y-m-d');
    $msg = "Enrollment opens:&nbsp;&nbsp;" . $date;
    if (!empty($msg)) {
      $status = '<div class="section-wait-list-status"  style="margin: 5px 0 0 0">' . $msg . '</div>';
    }
  }


/////////////
// CARD HEADER.
/////////////

$header_output = "
<div class='card-header' role='tab' id='sectionHeader$i'>
  <h5 class='mb-0'>
    <a data-toggle='collapse' data-parent='#sectionAccordion' href='#sectionCollapse$i'
      aria-expanded='" . ($in ? 'true' : 'false') . "'
      aria-controls='sectionCollapse$i'>
      " . $section_title . "
      <br><span class='sectionSemester'>$semester</span>" . "
      <br>" . (!empty($status) ? $status : "" ) . "
      <i class='fa fa-plus' style='display:" . $plus_style . ";'></i>
      <i class='fa fa-minus' style='display:" . $minus_style . ";'></i>
    </a>
  </h5>
</div>
";

/////////////
// CARD BODY.
/////////////

$body_output = '';
$body_section_fields = $config['body_section_fields'];

// GET ACTION BUTTON
$action_button = "";
if($body_section_fields['action_button']){
  // Get the action button.
  if (unh_d1_client_sectionIsAvailable($section)) {  
    $action_button = '<a class="btn btn-primary btn-block btn-enroll" ' . /* _d1pdt_get_enrollment_tracking_code($section) */ "" . ' href="' . unh_d1_client_get_enrollment_url($section) . '">Enroll Now</a>';
  } elseif (unh_d1_client_sectionIsWaitlisted($section)) {
    $action_button = '<a class="btn btn-primary btn-block btn-waitlist" href="' . unh_d1_client_get_wait_list_url($section) . '">Join Wait List</a>';
  } elseif (unh_d1_client_sectionIsFutureOffering($section)) {
    
  } elseif (unh_d1_client_sectionIsNoLongerAvailable($section)) {
    
  } elseif (unh_d1_client_sectionIsFull($section)) {
  
  } elseif (unh_d1_client_sectionIsEnrollmentClosed($section)) {
  
  } else {
    $action_button = "";
  }
  
  if (!empty($action_button)) {
    $action_button = "
<div class='section-enroll-btn'>
  ". $action_button ."
</div>";
  } 
}

/*
  $action_button = "";
  if (unh_d1_client_sectionIsWaitlisted($section)) {
    $action_button = '
<a class="btn btn-primary btn-block btn-waitlist" href="' . _d1pdt_get_wait_list_url($sectionID) . '">Join Wait List</a>';
  } elseif (unh_d1_client_sectionIsEnrollmentClosed($section)) {
    $action_button = '
<div class="btn btn-primary btn-block btn-enrollment-closed">Enrollment Closed</div>';
  } elseif (unh_d1_client_sectionIsFutureOffering($section)) {
    $action_button = _d1pdt_get_notify_me_button($course['objectId'], $section['oneCESectionNumber']);
  } else {
    $action_button = _d1pdt_get_enroll_now_button($sectionObjId, $section);
  }
*/

// GET SECTION DATES
$section_dates = "";
if($body_section_fields['section_dates']['show']){
  $section_schedules = unh_d1_client_getSectionSchedules($section);
  $dates = [];
  foreach($section_schedules as $section_schedule) {
    $start_date = unh_d1_client_getSectionScheduleStartDate($section_schedule);
    $end_date = unh_d1_client_getSectionScheduleEndDate($section_schedule);
    ddl($section_schedule, '$section_schedule - DATES!');
    ddl($start_date, '$start_date - DATES!');
    ddl($end_date, '$end_date - DATES!');
    if (($body_section_fields['section_dates']['options'] == UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_AND_END_DATE) && 
      !empty($start_date) && !empty($end_date)) 
    {
      if ($start_date == $end_date) {
        $dates[] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
      } else {
        $dates[] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT) . ' to ' . $end_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
      }
    } elseif (($body_section_fields['section_dates']['options'] == UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_DATE_ONLY) && 
      !empty($start_date)) { 
      $dates[] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
    }
  }
  
  if (!empty($dates)) {
    $dates_str = implode('<br>', $dates);
    $section_dates = "
<div class='section sectionDates'>
  <div class='row'>
    <div class='header col-xs-5'>
      <label for='sectionDates$i'>Dates:</label>
    </div>
    <div class='content col-xs-7'>
      <span id='sectionDates$i'>
        " . $dates_str . "
      </span>
    </div>
  </div>
</div>
";
  }
}

ddl($dates, '$dates - SECTION TEMPLATE');
// UNH_D1_DRUPAL_DATE_FORMAT
  //$section_dates .= _d1pdt_sectionDates_block($section, $i, (array_key_exists('section_dates', $body_section_fields ) ? $body_section_fields['section_dates'] : null));


// WRAP BODY BLOCK.
$body_output .= "
<div id='sectionCollapse$i' class='collapse " . ($in ? 'in' : '') ."' role='tabpanel' aria-labelledby='sectionHeader$i'>
  <div class='card-block'>" . 
    $action_button . "
    <div class='section sectionDescription'>" .
      $section_dates . "
    </div>
  </div>
</div>
";  

// WRAP SECTION BLOCK
$output .= "<div class='card'>$header_output$body_output</div><!--card-->";
?>


<?=$output?>

</div>  <!-- <?=$classes?> -->






