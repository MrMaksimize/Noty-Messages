<?php

/**
 * Implements hook_settings().
 * Configuration settings page.
 *
 * @return
 *    Array of the system settings form.
 */
function noty_messages_settings() {
  // Per message configs
  // clear out the form first
  $form = array();
  $form['noty_messages_settings'] = array(
    '#type' => 'vertical_tabs',
  );
  $message_types = drupal_map_assoc(array('global', 'status', 'warning', 'error'));
  $trimmed_types = drupal_map_assoc(array('status', 'warning', 'error'));
  $defaults = _noty_messages_get_config_keys($message_types, TRUE, 'global');
  // Generate global configuration tab
  $default_is_noty = $defaults['is_noty'];
  unset($default_is_noty['global']);
  noty_messages_generate_settings_form($form, 'global', $defaults, FALSE);
  // append the is_noty config
  $form['noty_messages_global_settings']['noty_messages_global_is_noty'] = array(
    '#type' => 'checkboxes',
    '#options' => drupal_map_assoc($trimmed_types),
    '#title' => t('Messages to display in noty format'),
    '#default_value' => $defaults['is_noty'],
    '#weight' => '-20',
  );

  // Generate fieldsets for the rest
  $defaults = _noty_messages_get_config_keys($message_types, TRUE, 'single');
  foreach ($trimmed_types as $message_type){
    $disabled = FALSE;
    if ($defaults['use_global'][$message_type] == TRUE || $default_is_noty[$message_type] != $message_type){
      $disabled = TRUE;
    }
    noty_messages_generate_settings_form($form, $message_type, $defaults, $disabled);
    //@todo buttons
    //@todo jquery_ui_easing
  }// foreach
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

function noty_messages_generate_settings_form(&$form, $message_type, $defaults, $disabled = FALSE){
  $settings_key = 'noty_messages_' . $message_type . '_settings';
  $form[$settings_key] = array(
    '#type' => 'fieldset',
    '#title' => t('@type messages', array('@type' => ucfirst($message_type))),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('Configuration for @type messages.', array('@type' => $message_type)),
    '#group' => 'noty_messages_settings',
  );
  if ($message_type != 'global'){
    $form[$settings_key]['noty_messages_' . $message_type . '_use_global'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Global Configuration'),
      '#description' => t('Check to ignore the message settings in this pane and relegate to globals'),
      '#default_value' => $defaults['use_global'][$message_type],
    );
  }
  // layout of messages on the screen
  $form[$settings_key]['noty_messages_' . $message_type . '_type'] = array(
    '#type' => 'select',
    '#title' => t('Message Type'),
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
  $form[$settings_key]['noty_messages_' . $message_type . '_layout'] = array(
    '#type' => 'select',
    '#title' => t('Message Layout'),
    '#options' => array(
      'layout_top' => t('Top'),
      'layout_top_center' => t('Top Center'),
      'layout_bottom' => t('Bottom'),
      'layout_center' => t('Center'),
      'layout_top_left' => t('Top Left'),
      'layout_top_right' => t('Top Right'),
    ),
    '#description' => t('Where the messages should appear on the screen'),
    '#default_value' => $defaults['layout'][$message_type],
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_text_align'] = array(
    '#type' => 'select',
    '#title' => t('Message Text Alignment'),
    '#options' => array(
      'text_left' => t('Left'),
      'text_right' => t('Right'),
      'text_center' => t('Center'),
      'text_justify' => t('Justify'),
    ),
    '#description' => t('How should the text inside the message be aligned'),
    '#default_value' => $defaults['text_align'][$message_type],
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#field_suffix' => t('ms'),
    '#size' => 60,
    '#description' => t('The time in milliseconds for the notice to fade in and fade out'),
    '#default_value' => $defaults['speed'][$message_type],
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#field_suffix' => t('ms'),
    '#size' => 60,
    '#description' => t('The time in milliseconds the notice will display for, before fading out.'),
    '#default_value' => $defaults['timeout'][$message_type],
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_closable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Closable'),
    '#description' => t('Check to enable close button.'),
    '#default_value' => $defaults['layout'][$message_type],
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_click_close'] = array(
    '#type' => 'checkbox',
    '#title' => t('Close on self click'),
    '#description' => t('Can the user dismiss the message by clicking on it'),
    '#default_value' => $defaults['click_close'][$message_type],
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_modal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Message Modal'),
    '#description' => t('Should the background fade out when message is displayed'),
    '#default_value' => $defaults['modal'][$message_type] ,
    '#disabled' => $disabled,
  );
  $form[$settings_key]['noty_messages_' . $message_type . '_admin_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable noty messages on admin paths'),
    '#description' => t('Checking this box will disable noty messages on admin paths,
      as determined by the path_is_admin() function.'),
    '#default_value' => $defaults['admin_path'][$message_type],
    '#disabled' => $disabled,
  );
}
/**
 * Form submission handler for the configuration form.
 *
 * @see noty_messages_settings()
 */
function noty_messages_settings_submit($form, &$form_state) {
  if (!form_get_errors()) {
    //compile arrays to store in variables
    $message_types = drupal_map_assoc(array('global', 'status', 'warning', 'error'));
    $trimmed_types = drupal_map_assoc(array('status', 'warning', 'error'));
    $values = array();
    //get globals first across all messages
    $config_keys = _noty_messages_get_config_keys(NULL, FALSE, 'global');
    foreach ($config_keys as $key => $value){
      $values[$key] = _noty_messages_set_default($message_types, $form_state['values']['noty_messages_global_' . $key]);
    }
    $config_keys = _noty_messages_get_config_keys(NULL, FALSE, 'single');
    foreach ($trimmed_types as $message_type){
      // set use_global for all messages regardless
      $values['use_global'][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_use_global'];
      if ($values['is_noty'][$message_type] == TRUE && $values['use_global'][$message_type] == FALSE){
        //override defaults here
        foreach ($config_keys as $key => $value){
          $values[$key][$message_type] = $form_state['values']['noty_messages_' . $message_type . '_' . $key];
        }
      }
      //always save use_global ?
    }
    foreach ($values as $key => $value){
      variable_set('noty_messages_' . $key, $value);
    }
    drupal_set_message(t('The configuration has been saved.'));
  }
}
