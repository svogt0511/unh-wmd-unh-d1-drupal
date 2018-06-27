<?php
  $output = '';
  $courses = $variables['course_profiles'];
  
  if (!empty($courses)) {

    //FILTER: sort courses, available first, unavailable last.
    $courses = unh_d1_drupal_sort_available_courses_first($courses);

    $str = '
<ul class="list__chevron course-list">';

    foreach ($courses as $course) {

      $course_has_drupal_node = TRUE;
      $course_has_certificates = TRUE;
    
      $ep_icon = '<i class="fa fa-external-link course-search-icon"></i>';
      $online_icon = '<i class="fa fa-bolt course-search-icon"></i>';

      //FILTER: This controls the listing of applicable certificates in course search results.
      $list_applicable_certificates = FALSE;
      $list_online = TRUE;
      $list_external_partner = TRUE;
      $course_is_online = FALSE;
      $course_is_externalPartner = FALSE;
      if (!empty(unh_d1_client_getcourseNumber($course))) {
        $course_is_available = unh_d1_client_courseIsAvailable($course);
      } else {
        $course_is_available = unh_d1_drupal_non_d1_course_is_available($course['node']);
        $course_is_externalPartner = unh_d1_drupal_non_d1_course_is_externalPartner($course['node']);
        $course_is_online = unh_d1_drupal_non_d1_course_is_online($course['node']);
      }

      if (empty($course['applicableCertificates'])) {
        $course_has_certificates = FALSE;
      }
      if (empty($course['courseURL'])) {
        $course_has_drupal_node = FALSE;
      }

      $str .= '
  <li class="course-row">';

      if ($course_has_drupal_node) {
        $str .=  (!$course_is_available ? '
    <span class="course-unavailable">(Currently Unavailable - Request More Information)</span> ' : '') . '
    <a href="' . $course['courseURL']  . '"' . (!$course_is_available ? ' class="course-unavailable"' : '') . '>' .  $course['courseTitle'] . '</a>' .
        (($list_online && $course_is_online) ?  $online_icon : '') .
        (($list_external_partner && $course_is_externalPartner) ? $ep_icon : '');
      } else {
        $str .= '
    <span class="course-error">' . $course['courseTitle'] . '</span>';
      }

      if ($list_applicable_certificates && $course_has_certificates) {
         $str .= unh_d1_drupal_get_applicable_certificates_block($course);
      }

      $str .= '
  </li>';
    }

    $str .= '
</ul>';
  }
  
  $output = $str;
?>

<?=$output?> 
