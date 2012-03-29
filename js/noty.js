var notyMessages = notyMessages || {};

(function($) {
  Drupal.behaviors.notyMessagesRenderMessages = {
    attach: function(context, settings) {
      // don't deal with config here
      allMessages = settings.notyMessagesNoties;
      for (var type in allMessages){
        // pre construct the settings for noty
        notyMessages.renderType(type, allMessages[type], settings.notyMessages);
      }
    }
  }
  notyMessages.renderType = function(typeName, typeData, config){
    var notySettings  = {
      layout: config.notyLayout[typeName],
      type: config.notyType[typeName],
      textAlign: config.notyTextAlign[typeName],
      speed: config.notySpeed[typeName],
      timeout: config.notyTimeout[typeName],
      closable: config.notyClosable[typeName],
      closeOnSelfClick: config.notyClickClose[typeName],
      modal: config.notyModal[typeName],
      theme: config.notyTheme[typeName]
    }
    if (!(typeData instanceof Array)){
      typeData = new Array(typeData);
    }
    for (message in typeData){
      // set the text
      notySettings.text = typeData[message];
      noty(notySettings);
    }
  }
})(jQuery);