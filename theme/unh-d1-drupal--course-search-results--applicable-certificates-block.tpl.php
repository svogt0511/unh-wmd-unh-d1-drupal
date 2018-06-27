<?php
  $output = '';
  $course = $variables['course'];
  
  if (!empty($course) && !!empty($course['applicableCertificates'])) {

    // todo - get applicable certificates
    //$certificates = d1client_utils_get_course_applicableCertificates($course);
    $certificates = array();

    $str = '
<ul class="certificates-block">';
    foreach($certificates as $certificate) {
      $str .= '
  <li><span style="font-weight: 600;">Applicable Certificate:</span> ' . $certificate['name'] . '  (' . $certificate['code'] . ')</li>';
    }
    $str .= '
</ul>';
  }
  
  $output = $str;
?>

<?=$output?>
