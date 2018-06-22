<?php

/**
 * @file
 *
 * Functions for Non-D1 courses.  Equivalent to D1 functions for D1 courses.
 * Perhaps this should be in a separate module.
 *
 */
 
/**
 * Given a course structure, returns the drupal course node if it is a non-d1 course, otherwise returns NULL.
 */
function unh_d1_drupal_get_course_node($course) {
  $ret =  NULL;
  
  if (!empty($course)) {
    if (array_key_exists('node', $course)) {
      $ret = $course['node'];
    }
  }
    
  return $ret;
}

/**
 * Given course node, returns course status.
 */
function unh_d1_drupal_non_d1_course_is_available($node) {
  $ret = FALSE;
  
  if (!empty($node)) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $course_code = $wrapper->field_course_code->value();
    if (empty($wrapper->field_course_code->value())) {
      $availability = $wrapper->field_course_availability->value();
      $ret = ((strcasecmp($availability, UNH_D1_DRUPAL_NON_D1_COURSE_IS_AVAILABLE) == 0) ? TRUE : FALSE);
    }
  }

  return $ret;
}

/**
 * Given course node, returns course title.
 */
function _unh_d1_drupal_non_d1_course_title($node) {
  $ret = '';
  
  $wrapper = entity_metadata_wrapper('node', $node);
  $ret = $wrapper->title->value();
  
  return $ret;
}

/**
 * Given course node, returns course enrollment url.
 */
function _unh_d1_drupal_non_d1_course_enrollment_url($node) {
  $ret = '';

  if (!empty($node)) {
    $ret = (!empty($node->field_course_enrollment_link) ? $node->field_course_enrollment_link['und'][0]['url'] : "");
  }

  return $ret;
}

/**
 * Given course node, returns Course schedule (dates/times).
 */
function _unh_d1_drupal_non_d1_course_schedule($node) {
  $ret = array();

  if (!empty($node) && !empty($node->field_course_dates_times)) {
    $node_wrapper = entity_metadata_wrapper('node', $node);

    foreach ($node_wrapper->field_course_dates_times as $field_collection_wrapper) {
      $course_sched = $field_collection_wrapper->value();

      $date_time = array(
        'start_date' => NULL,
        'end_date' => NULL,
        'start_time' => NULL,
        'end_time' => NULL,
      );

      if (!empty($course_sched->field_course_start_end_date)) {
        $dates = $course_sched->field_course_start_end_date['und'][0];
        if (!empty($dates['value']) && !empty($dates['value2'])) {
          $start_date = (new DateTime($dates['value'], new DateTimeZone($dates['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          $end_date = (new DateTime($dates['value2'], new DateTimeZone($dates['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          if ($start_date == $end_date) {
            $date_time['start_date'] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
          } else {
            $date_time['start_date'] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
            $date_time['end_date'] = $end_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
          }
        } elseif (!empty($dates['value'])) {
          $start_date = (new DateTime($dates['value'], new DateTimeZone($dates['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          $date_time['start_date'] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
        } elseif (!empty($dates['value2'])) {
          $start_date = (new DateTime($dates['value2'], new DateTimeZone($dates['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          $date_time['start_date'] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
        }
      }

      if (!empty($course_sched->field_course_start_end_time)) {
        $times = $course_sched->field_course_start_end_time['und'][0];
        if (!empty($times['value']) && !empty($times['value2'])) {
          $start_time = (new DateTime($times['value'], new DateTimeZone($times['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          $end_time = (new DateTime($times['value2'], new DateTimeZone($times['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          if ($start_time == $end_time) {
            $date_time['start_time'] = $start_time->format(UNH_D1_DRUPAL_TIME_FORMAT);
          } else {
            $date_time['start_time'] = $start_time->format(UNH_D1_DRUPAL_TIME_FORMAT);
            $date_time['end_time'] = $end_time->format(UNH_D1_DRUPAL_TIME_FORMAT);
          }
        } elseif (!empty($dates['value'])) {
          $start_date = (new DateTime($dates['value'], new DateTimeZone($dates['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          $date_time['start_date'] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
        } elseif (!empty($dates['value2'])){
          $start_date = (new DateTime($dates['value2'], new DateTimeZone($dates['timezone_db'])))->setTimezone(new DateTimeZone($dates['timezone']));
          $date_time['start_date'] = $start_date->format(UNH_D1_DRUPAL_DATE_FORMAT);
        }
      }

      $ret[] = $date_time;
    }
  }

// Here is where we get the time. (loop through the field collections).
/*  $ret = array(
    array(
      'start_date' => '10 Jan 2018',
      'end_date' => '20 Jan 2018',
      'start_time' => '01:00am',
      'end_time' => '02:00am'
    ),
    array(
      'start_date' => '10 Feb 2018',
      'end_date' => '20 Feb 2018',
      'start_time' => '02:00am',
      'end_time' => '03:00am'
    ),
  );
*/
  return $ret;
}

/**
 * Given course node, returns course location.
 */
function _unh_d1_drupal_non_d1_course_location($node) {
  $ret = '';
  
  if (!empty($node)) {
    $ret = (!empty($node->field_course_location_name) ? $node->field_course_location_name['und'][0]['value'] : "");
  }

  return $ret;
}
 
/**
 * Given course node, returns array of course instructors.
 */
function _unh_d1_drupal_non_d1_course_instructors($node) {
  $ret = array();

  if (!empty($node) && !empty($node->field_instructor_bio)) {
    foreach ($node->field_instructor_bio['und'] as $target) {
      $target_id = $target['target_id'];
      $instructor_bio = node_load($target_id);
      $ret[] = $instructor_bio->title;
    }
  }

  return $ret;
}

/**
 * Given course node, returns a url to the course page.
 */
function _unh_d1_drupal_non_d1_course_url($node) {
  $ret = '';

  if (!empty($node)) {
   $ret = url(drupal_get_path_alias('node/' . $node->nid));
  }

  return $ret;
}


/**
 * Given course node, returns a money-formatted cost.
 */
function _unh_d1_drupal_non_d1_course_tuition($node) {
  $ret = '';

  if (!empty($node)) {
    $tuition = (!empty($node->field_course_tuition) ? $node->field_course_tuition['und'][0]['value'] : "");
    $ret = $tuition;
  }
  
  return $ret;
}

/**
 * Given course node, returns contact hours.
 */
function _unh_d1_drupal_non_d1_course_contact_hours($node) {
  $ret = '';

  if (!empty($node)) {
    $ret = (!empty($node->field_course_contact_hours) ? $node->field_course_contact_hours['und'][0]['value'] : "");
  }

  return $ret;
}

/**
 * Given course node, returns ceus.
 */
function _unh_d1_drupal_non_d1_course_ceus($node) {
  $ret = '';

  if (!empty($node)) {
    $ret = (!empty($node->field_course_ceus) ? $node->field_course_ceus['und'][0]['value'] : "");
  }

  return $ret;
}

