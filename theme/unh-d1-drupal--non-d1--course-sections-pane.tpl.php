<?php
if (!empty($course_nid)) {
  $node = node_load($course_nid);
  if (!empty($node)) {
?> 
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div id="ajax-target-801725"></div>
  <div id="ajax-target-801751"></div>  
  <div id="ajax-target"></div>

  <div class='course-info_pane'>

<?php
    $output = '';
    $course_is_available =_unh_d1_drupal_non_d1_course_is_available($node);
    if ($course_is_available) {
      $course_title = _unh_d1_drupal_non_d1_course_title($node);
      $enrollment_url = _unh_d1_drupal_non_d1_course_enrollment_url($node);
      $dates_times = _unh_d1_drupal_non_d1_course_schedule($node);
      $location_name = _unh_d1_drupal_non_d1_course_location($node);
?>
    <div class='card course-info-pane'>
      <div class='card-header' role='tab' id='courseHeader'>
        <h5 class='mb-0'>
          <a href='$current_url'>
            <?=$course_title?>
          </a>
        </h5>
      </div>  <!-- card-header -->

      <div class='card-block'>

<?php
      if (!empty($enrollment_url)) {
?>
        <div class='section-enroll-btn'>
          <a class='btn btn-primary btn-block btn-enroll' target='_blank' href='<?=$enrollment_url?>'>Enroll Now</a>
        </div>
<?php
      } 
?>     
        <div class='section sectionDescription'>
<?php
      if (!empty($dates_times)) {
?>
          <div class='section sectionDates'>
            <div class='row'>
              <div class='header col-xs-5'>
                <label for='courseDates'>Dates:</label>
              </div>
              <div class='content col-xs-7'>
                <span id='courseDates'>
<?php
        foreach($dates_times as $date_time) {
          $start_date = $date_time['start_date'];
          $end_date = $date_time['end_date'];

          if (!empty($end_date)) {
?>    
                  <div class='course-date-wrapper'><div class='course-date'><?=$start_date?></div> - <div class='course-date'><?=$end_date?></div></div>
<?php
          } else {
?>
                  <div class='course-date-wrapper'><div class='course-date'><?=$start_date?></div></div>
<?php
          }
        }
?>
                </span>
              </div>
            </div> <!-- row -->
          </div> <!-- section sectionDates -->

          <div class='section sectionTimes'>
            <div class='row'>
              <div class='header col-xs-5'>
                <label for='courseTimes'>Times:</label>
              </div>
              <div class='content col-xs-7'>
                <span id='courseTimes'>
<?php
        foreach($dates_times as $date_time) {
          $start_time = $date_time['start_time'];
          $end_time = $date_time['end_time'];

          if (!empty($end_time)) {
?>
                  <div class='course-time-wrapper'><div class='course-time'><?=$start_time?></div> - <div class='course-date'><?=$end_time?></div></div>
<?php
          } else {
?>
                  <div class='course-time-wrapper'><div class='course-time'><?=$start_time?></div></div>
<?php
          }
        }
?>
                </span> <!-- courseTimes -->
              </div>
            </div> <!-- row -->
          </div> <!-- section sectionTimes -->
<?php          
        if (!empty($location_name)) {
?>
          <div class='section item courseLocation'>
            <div class='row'>
              <div class='header col-xs-5'>
                <label for='courseLocation'>Location:</label>
              </div>
              <div class='content col-xs-7'>
                <span id='courseLocation'>
                  <?=$location_name?>
                </span>
              </div>
            </div> <!-- row -->
          </div>
<?php
        }     
      } else {
        // Commented this out - shows nothing on 'section unavailable'.
        $output .= "<!-- <div class='section-unavailable'>$sectionTitle (UNAVAILABLE $sectionSemester)</div> -->";
      }
  
?>
  </div> <!--course-info_pane--> 
</div> <!--<?=$classes?>-->
<?php
    }
  }
}
?>

