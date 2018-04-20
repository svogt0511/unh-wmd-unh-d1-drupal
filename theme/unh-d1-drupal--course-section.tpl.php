<div class="<?=$classes?>"<?=$attributes?>> 
<?php 
ddl("SECTION TEMPLATE BEGIN");
ddl($variables, '$variables - template');
ddl("SECTION TEMPLATE END");

// Normally, there would be a number of themed blocks here, but we don't have the time.
// This seems to be a reasonable organization for now.  More can be done later.
// @todo: theme these better!!!

/////////////
// CARD HEADER.
/////////////

$sectionTitle = unh_d1_client_getsectionTitle($section);
$sectionNumber = unh_d1_client_getsectionCustomSectionNumber($section);
$node = node_load($course_nid);
$course_code = unh_d1_client_getcourseNumber($course);

$i = $section_num;
$in = $disp_open;
$semester = unh_d1_client_getsectionSemester($section);
$section_title = unh_d1_client_getsectionTitle($section);
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

// GET HEADER OUTPUT
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
$body_section_fields = $config;

// GET ACTION BUTTON
if(in_array('action_button', $body_section_fields)){

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
  $action_button = "
<div class='section-enroll-btn'>
  ". $action_button ."
</div>";

// GET SECTION DATES
if( in_array( 'section_dates', $body_section_fields) || array_key_exists( 'section_dates', $body_section_fields) ){

  $section_dates .= _d1pdt_sectionDates_block($section, $i, (array_key_exists('section_dates', $body_section_fields ) ? $body_section_fields['section_dates'] : null));

}

$section_dates = '';

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