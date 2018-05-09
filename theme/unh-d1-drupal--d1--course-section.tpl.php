<?php
if (!empty($course) && !empty($section)) {
?>
<div class="<?=$classes?>"<?=$attributes?>> <!-- <?=$classes?> -->
<?php 

// Normally, there would be a number of themed blocks here, but we don't have the time.
// This seems to be a reasonable organization for now.  More can be done later.
// @todo: theme these better!!!

$sectionTitle = unh_d1_client_getsectionTitle($section);
$sectionNumber = unh_d1_client_getsectionCustomSectionNumber($section);
$node = node_load($course_nid);
$course_code = unh_d1_client_getcourseNumber($course);
$semester = unh_d1_client_getsectionSemester($section);
$section_title = unh_d1_client_getsectionTitle($section);
$contact_hours = unh_d1_client_getsectionContactHours($section);
$ceus = unh_d1_client_getsectionCEUs($section);
$discounts = unh_d1_client_getsectionDiscountNames($section);

$i = $disp_idx;
$in = $disp_open;
$plus_style = ($in ? "none" : "inline");
$minus_style = ($in ? "inline" : "none");
$output = '';

// DETERMINE SECTION STATUS.
  $status = '';
  if (unh_d1_client_sectionIsWaitlisted($section)) {
    $status = '<div class="section-wait-list-status" style="5px 0 0 0">Wait List</div>';
  } elseif (unh_d1_client_sectionIsFull($section)) {
    $status = '<div class="section-full-status" style="5px 0 0 0">Full</div>';
  } elseif (unh_d1_client_sectionIsEnrollmentClosed($section)) {
    $status = '<div class="section-enrollment-closed-status" style="5px 0 0 0">Enrollment Closed</div>';
  } elseif (unh_d1_client_sectionIsFutureOffering($section)) {
    $dt = unh_d1_client_getSectionEnrollmentBeginDate($section);
    $date = $dt->format(UNH_D1_DRUPAL_DATE_FORMAT);
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
    $action_button = '<a class="btn btn-primary btn-block btn-request-more-info" href="' . unh_d1_client_get_request_more_info_url($section) . '">Notify Me When Enrollment Opends</a>';     
  } elseif (unh_d1_client_sectionIsNoLongerAvailable($section)) {
    // $action_button = '<a class="btn btn-primary btn-block btn-request-more-info" href="' . unh_d1_client_get_request_more_info_url($section) . '">Request Information</a>';  
  } elseif (unh_d1_client_sectionIsFull($section)) {
    $action_button = '<a class="btn btn-primary btn-block btn-request-more-info" href="' . unh_d1_client_get_request_more_info_url($section) . '">Request Information</a>';  
  } elseif (unh_d1_client_sectionIsEnrollmentClosed($section)) {
    $action_button = '<a class="btn btn-primary btn-block btn-request-more-info" href="' . unh_d1_client_get_request_more_info_url($section) . '">Request Information</a>';    
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

////
// GET SECTION DATES
$section_dates = "";
if($body_section_fields['section_dates']['show']){
  $section_schedules = unh_d1_client_getSectionSchedules($section);
  $dates = [];
  foreach($section_schedules as $section_schedule) {
    $start_date = unh_d1_client_getSectionScheduleStartDate($section_schedule);
    $end_date = unh_d1_client_getSectionScheduleEndDate($section_schedule);
    if (($body_section_fields['section_dates']['options'] == UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_AND_END_DATE) && 
      !empty($start_date) && !empty($end_date)) 
    {
      if ($start_date == $end_date) {
        $dates[] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
      } else {
        $dates[] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT) . ' - ' . $end_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
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
////
// GET SECTION TIMES
$section_times = "";
if($body_section_fields['section_times']['show']) {
  $section_schedules = unh_d1_client_getSectionSchedules($section);
  $times = [];
  foreach($section_schedules as $section_schedule) {
    $start_time = unh_d1_client_getSectionScheduleStartTime($section_schedule);
    $end_time = unh_d1_client_getSectionScheduleEndTime($section_schedule);
    if (($body_section_fields['section_times']['options'] == UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_AND_END_TIME) && 
      !empty($start_time) && !empty($end_time)) 
    {
      if ($start_time == $end_time) {
        $times[] = $start_time->format(UNH_D1_DRUPAL_TIME_FORMAT);
      } else {
        $times[] = $start_time->format(UNH_D1_DRUPAL_TIME_FORMAT) . ' - ' . $end_time->format(UNH_D1_DRUPAL_TIME_FORMAT);
      }
    } elseif (($body_section_fields['section_times']['options'] == UNH_D1_DRUPAL_BODY_SECTIONS_SHOW_START_TIME_ONLY) && 
      !empty($start_time)) { 
      $times[] = $start_time->format(UNH_D1_DRUPAL_TIME_FORMAT);
    }
  }
  
  if (!empty($times)) {
    $times_str = implode('<br>', $times);
    $section_times = "
<div class='section sectionTimes'>
  <div class='row'>
    <div class='header col-xs-5'>
      <label for='sectionTimes$i'>Times:</label>
    </div>
    <div class='content col-xs-7'>
      <span id='sectionTimes$i'>
        " . $times_str . "
      </span>
    </div>
  </div>
</div>
";
  }
}

////
// GET SECTION LOCATION/CAMPUS
$section_locations = "";
if($body_section_fields['section_locations']){
  $section_schedules = unh_d1_client_getSectionSchedules($section);
  $locations = [];
  foreach($section_schedules as $section_schedule) {
    $location = unh_d1_client_getSectionCampusName($section_schedule);
    if (!empty($location)) {
      $locations[] = $location;
    }
  }
  if (!empty($locations)) {
    $section_locations .= "
<div class='section item courseLocation'>
  <div class='row'>
    <div class='header col-xs-5'>
      <label for='courseLocation'>Location:</label>
    </div>
    <div class='content col-xs-7'>
      <span id='courseLocation'>"
        . implode('<br>', $locations) . "
      </span>
    </div>
  </div> <!-- row -->
</div>";
  }
}

////
// GET SECTION INSTRUCTORS
$section_instructors = "";
if($body_section_fields['section_instructors']){
  $section_schedules = unh_d1_client_getSectionSchedules($section);
  $instructors = [];
  foreach($section_schedules as $section_schedule) {
    $instructor_list = unh_d1_client_getSectionInstructorNames($section_schedule);
    if (!empty($instructor_list)) {
      $instructors = $instructors + $instructor_list;
    }
  }
  
  if (!empty($instructors)) {
    $section_instructors = "
<div class='section item courseInstructors'>
  <div class='row'>
    <div class='header col-xs-5'>
      <label for='courseInstructors'>Instructor(s):</label>
    </div>
    <div class='content col-xs-7'>
      <span id='courseInstructors'>";

  foreach($instructors as $instructor) {
      $section_instructors .= "
        <div class='course-instructor'>$instructor</div>";
  }

  $section_instructors .= "
      </span>
    </div>
  </div> <!-- row -->
</div> <!-- section item courseInstructors -->";
  }
}

////
// GET SECTION TUITION
$section_tuition = "";
if ($body_section_fields['section_tuition']['show']) {
  $field_label = (!empty($body_section_fields['section_tuition']['label']) ? $body_section_fields['section_tuition']['label'] : 'Tuition:');
  $show_published_code = $body_section_fields['section_tuition']['published_code'];
  $tuition_items = unh_d1_client_getSectionTuitionInfo($section);  
  $tuition = [];
  setlocale(LC_MONETARY, 'en_US.UTF-8');
  foreach($tuition_items as $tuition_item) {
    $amounts_raw = array_column($tuition_item['items'], 'amount');
    $amounts = [];
    foreach ($amounts_raw as $amount) {
      $amounts[] = money_format('%.2n', $amount);
    }
    $tuition[] = implode(($show_published_code ? (!empty($tuition_item['published_code']) ? ' <span class="published-code">' . $tuition_item['published_code'] . '</span>' : '') : '') . '<br>', $amounts) .
      ($show_published_code ? (!empty($tuition_item['published_code']) ? ' <span class="published-code">' . $tuition_item['published_code'] . '</span>' : '') : '');
  }
  
  if (!empty($tuition)) {
    $tuition_str = implode('<br>', $tuition);
    $section_tuition = "
<div class='section item courseTuition'>
  <div class='row'>
    <div class='header col-xs-5'>
      <label for='courseTuition$i'>" . $field_label . "</label>
    </div>
    <div class='content col-xs-7'>
      <span id='courseTuition$i'>
        " . $tuition_str . "
      </span>
    </div>
  </div>
</div>
";
  }
}

////
// GET SECTION CONTACT HOURS
$section_contact_hours = '';
if ($body_section_fields['section_contact_hours'] && !empty($contact_hours)) {
  $section_contact_hours = "
<div class='section item sectionContactHours'>
  <div class='row'>
    <div class='header col-xs-5'>
      <label for='sectionContactHours$i'>Contact Hours:</label>
    </div>
    <div class='content col-xs-7'>
      <span id='sectionContactHours$i'>
        " . $contact_hours . "
      </span>
    </div>
  </div>
</div>
";
}


////
// GET SECTION DISCOUNTS
$section_discounts = '';
if ($body_section_fields['section_discounts'] && !empty($discounts)) {
  $discounts_str = implode('<br>', $discounts);
  $section_discounts =  "
  <div class='section item courseDiscounts'>
    <div class='row'>
      <div class='header col-xs-5'>
        <label for='courseDiscounts$i'>Potential Discount(s):</label>
      </div>
      <div class='content col-xs-7'>
        <span id='courseDiscounts$i'>
          " . $discounts_str . "
        </span>
      </div>
    </div>
  </div>
";
}

////
// GET SECTION CEUs
$section_ceus = '';
if ($body_section_fields['section_contact_hours'] && !empty($ceus)) {
  $section_ceus = "
  <div class='section item sectionCEUs'>
    <div class='row'>
      <div class='header col-xs-5'>
        <label for='sectionCEU$i'>CEU(s):</label>
      </div>
      <div class='content col-xs-7'>
        <span id='sectionCEU$i'>
          " . $ceus . "
        </span>
      </div>
    </div>
  </div>
";
}

////
// GET SECTION COURSE CODE
$section_course_code = "";
if($body_section_fields['section_course_code'] && !empty($course_code)) {
  $section_course_code = "
  <div class='section item courseCode'>
    <div class='row'>
      <div class='header col-xs-5'>
        <label for='courseCode$i'>Course Code:</label>
      </div>
      <div class='content col-xs-7'>
        <span id='courseCode$i'>
          " . $course_code . "
          </span>
      </div>
    </div>
  </div>
";
}

////
// GET SECTION NUMBER section_number
$section_number = '';
if($body_section_fields['section_number'] && !empty($sectionNumber)) {
  $section_number = "
  <div class='section item sectionNumber'>
    <div class='row'>
      <div class='header col-xs-5'>
        <label for='sectionNumber$i'>Section Number:</label>
      </div>
      <div class='content col-xs-7'>
        <span id='sectionNumber$i'>
"
    . $sectionNumber .
    "       </span>
      </div>
    </div>
  </div>
";
}

// WRAP BODY BLOCK.
$body_output .= "
<div id='sectionCollapse$i' class='collapse " . ($in ? 'in' : '') ."' role='tabpanel' aria-labelledby='sectionHeader$i'>
  <div class='card-block'>" . 
    $action_button . "
    <div class='section sectionDescription'>" .
      $section_dates . 
      $section_times . 
      $section_locations .
      $section_instructors .
      $section_tuition . 
      $section_contact_hours . 
      $section_discounts . 
      $section_ceus . 
      $section_course_code . 
      $section_number . "
    </div>
  </div>
</div>
";  

// WRAP SECTION BLOCK
$output .= "<div class='card'>$header_output$body_output</div><!--card-->";
?>


<?=$output?>

</div>  <!-- <?=$classes?> -->
<?php
} // !empty($section)






