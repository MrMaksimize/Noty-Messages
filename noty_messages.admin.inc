<?php

/**
 * @return
 *    Array of the system settings form.
 */
function noty_messages_admin_settings() {
  // Per message configs
  // clear out the form first
  noty_messages_messages_setup();
  drupal_add_js(drupal_get_path('module', 'noty_messages') . '/js/noty_admin_form.js');
  $form = array();
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
  );
  $message_types = _noty_messages_get_types();
  $defaults = _noty_messages_get_config_keys($message_types['all'], TRUE, 'global');
  // Generate global configuration tab
  $default_is_noty = $defaults['is_noty'];
  unset($default_is_noty['global']);
  $lib_exists = is_file(libraries_get_path('noty') . '/js/jquery.noty.js');
  $disabled = FALSE;
  if (!$lib_exists) {
    $form['code_status'] = array(
      '#type' => 'fieldset',
      '#title' => t('Purr Messages settings'),
      '#weight' => '-10',
      '#description' => t('Please download the noty library from https://github.com/needim/noty and place it in the libraries/noty directory. So that jquery.noty.js file is located in libraries/noty/js/jquery.noty.js'),
    );
    $disabled = TRUE;
  }
  noty_messages_generate_settings_form($form, 'global', $defaults, $disabled);
  // append the is_noty config
  $form['settings']['global']['is_noty'] = array(
    '#type' => 'checkboxes',
    '#options' => $message_types['trimmed'],
    '#title' => t('Messages to display in noty format'),
    '#default_value' => $defaults['is_noty'],
    '#weight' => '-5',
    '#disabled' => $disabled,
  );

  // Generate fieldsets for the rest
  $defaults = _noty_messages_get_config_keys($message_types['all'], TRUE, 'single');
  foreach ($message_types['trimmed'] as $message_type) {
    $disabled = FALSE;
    if (!empty($defaults['use_global'][$message_type]) || empty($default_is_noty[$message_type]) || !$lib_exists) {
      $disabled = TRUE;
    }
    noty_messages_generate_settings_form($form, $message_type, $defaults, $disabled);
    // @todo buttons
    // @todo jquery_ui_easing
  }// foreach
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    ),
    'reset' => array(
      '#type' => 'submit',
      '#value' => t('Reset All Settings'),
      '#submit' => array('noty_messages_settings_reset'),
    ),
  );
  return $form;
}

function noty_messages_generate_settings_form(&$form, $message_type, $defaults, $disabled = FALSE) {
  //$settings_key = 'noty_messages_' . $message_type . '_settings';
  $settings_key = $message_type;
  $form['settings'][$message_type] = array(
    '#type' => 'fieldset',
    '#title' => t('@type messages', array('@type' => ucfirst($message_type))),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('Configuration for @type messages.', array('@type' => $message_type)),
    '#group' => 'noty_messages_settings',
  );
  if ($message_type != 'global') {
    $form['settings'][$message_type]['use_global'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use global configuration'),
      '#description' => t('Check to ignore the message settings in this pane and relegate to globals'),
      '#default_value' => empty($defaults['use_global'][$message_type]) ? TRUE : FALSE,
    );
  }
  // Message display
  $form['settings'][$message_type]['type'] = array(
    '#type' => 'select',
    '#title' => t('Message type'),
    '#options' => array(
      'alert' => t('Alert'),
      'error' => t('Error'),
      'success' => t('Success'),
    ),
    '#description' => t('How To Theme or smth like that'),
    '#default_value' => $defaults['type'][$message_type],
    '#disabled' => $disabled,
  );

  // layout of messages on the screen
  $form['settings'][$message_type]['layout'] = array(
    '#type' => 'select',
    '#title' => t('Message layout'),
    '#options' => array(
      'top' => t('Top'),
      'topCenter' => t('Top Center'),
      'bottom' => t('Bottom'),
      'center' => t('Center'),
      'topLeft' => t('Top Left'),
      'topRight' => t('Top Right'),
    ),
    '#description' => t('Where the messages should appear on the screen'),
    '#default_value' => $defaults['layout'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['text_align'] = array(
    '#type' => 'select',
    '#title' => t('Message text alignment'),
    '#options' => array(
      'left' => t('Left'),
      'right' => t('Right'),
      'center' => t('Center'),
      'justify' => t('Justify'),
    ),
    '#description' => t('How should the text inside the message be aligned'),
    '#default_value' => $defaults['text_align'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#field_suffix' => t('ms'),
    '#size' => 60,
    '#description' => t('The time in milliseconds for the notice to fade in and fade out'),
    '#default_value' => $defaults['speed'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#field_suffix' => t('ms'),
    '#size' => 60,
    '#description' => t('The time in milliseconds the notice will display for, before fading out.'),
    '#default_value' => $defaults['timeout'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['closable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Closable'),
    '#description' => t('Check to enable close button.'),
    '#default_value' => $defaults['closable'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['click_close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close on self click'),
    '#description' => t('Can the user dismiss the message by clicking on it'),
    '#default_value' => $defaults['click_close'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['modal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Message modal'),
    '#description' => t('Should the background fade out when message is displayed'),
    '#default_value' => $defaults['modal'][$message_type] ,
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['admin_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable noty messages on admin paths'),
    '#description' => t('Checking this box will disable noty messages on admin paths,
      as determined by the path_is_admin() function.'),
    '#default_value' => $defaults['admin_path'][$message_type],
    '#disabled' => $disabled,
  );
  $form['settings'][$message_type]['test_noty'] = array(
    '#type' => 'button',
    '#value' => t("Test @type messages", array('@type' => $message_type)),
    '#name' => $message_type,
    '#attributes' => array('class' => array('test-noty-messages')),
  );
}

/**
 * Form submission handler for the configuration form.
 *
 * @see noty_messages_settings()
 */
function noty_messages_admin_settings_submit($form, &$form_state) {
  if (!form_get_errors()) {
    // compile arrays to store in variables
    $message_types = _noty_messages_get_types();
    $values = array();
    // pull globals out.
    $single_settings = $form_state['values']['settings'];
    $single_settings = array_intersect_key($single_settings, array_flip(array_values($message_types['all'])));
    $global_settings = $single_settings['global'];
    unset($single_settings['global']);
    // filter out unneeded configs
    $config_keys = _noty_messages_get_config_keys(NULL, FALSE, 'global');
    $global_settings = array_intersect_key($global_settings, array_flip($config_keys));
    foreach ($global_settings as $setting_name => $setting){
      $values[$setting_name] = _noty_messages_get_default($message_types['all'], $setting);
    }
    foreach ($single_settings as $message_type => $settings){
      $config_keys = _noty_messages_get_config_keys(NULL, FALSE, 'single');
      $settings = array_intersect_key($settings, array_flip($config_keys));
      // check to make sure that it's not set to use globals and that it is a noty message type
      if ((bool)$settings['use_global'] != TRUE && (bool)$values['is_noty'][$message_type] != FALSE){
        // get the settings in
        foreach($settings as $setting_name => $setting){
          $values[$setting_name][$message_type] = $setting;
        }
      }
    }
    foreach ($values as $key => $value) {
      variable_set('noty_messages_' . $key, $value);
    }
    drupal_set_message(t('The configuration has been saved.'));

    /*foreach ($config_keys as $key) {
      $values[$key] = _noty_messages_get_default($message_types['all'], $form_state['values']['noty_messages_global_' . $key]);
    }
    $config_keys = _noty_messages_get_config_keys(NULL, FALSE, 'single');
    foreach ($message_types['trimmed'] as $message_type) {
      // set use_global for all messages regardless
      $values['use_global'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_use_global'];
      if ($values['is_noty'][$message_type] == TRUE && $values['use_global'][$message_type] == FALSE) {
        //override defaults here
        foreach ($config_keys as $key) {
          $values[$key][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_' . $key];
        }
      }
    }*/
  }
}

function noty_messages_settings_reset($form, &$form_state){
  $message_types = _noty_messages_get_types();
  $defaults = _noty_messages_get_config_keys($message_types['all'], FALSE, 'all');
  foreach ($defaults as $key => $value) {
    variable_del('noty_messages_' . $value);
  }
}

