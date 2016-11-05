// idlakcex/cexfunctions.cc

// Copyright 2013 CereProc Ltd.  (Author: Matthew Aylett)

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
// WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache 2 License for the specific language governing permissions and
// limitations under the License.
//

// Each function fills a feature extraction buffer up with a feature based on
// an XML node and context.

// Function names are of the form CexFunc[CUR|PRE|PST][INT|STR][feature name]
// i.e. CexFuncCURINTp0

// if the function returns false cex appends the NULL value defined in the
// architecture

// if the function throws an error cex appends the ERROR value, reports and
// tries to continue

#include "idlaktxp/txpcexspec.h"
bool isVowel(std::string phone);
namespace kaldi {


// previous previous phone name
bool CexFuncStringBackwardBackwardPhone(const TxpCexspec* cex,
                      const TxpCexspecFeat* feat,
                      const TxpCexspecContext* context,
                      std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* phonename;
  // get node from correct context
  node = context->GetPhone(-2, feat->pause_context);
  // check for NULL value
  if (node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // extract value from XML
    phonename = node.attribute("val").value();
    // check and append value
    okay = cex->AppendValue(*feat, okay, phonename, buffer);
  }
  // return error status
  return okay;
}

// previous phone name
bool CexFuncStringBackwardPhone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* phonename;
  // get node from correct context
  node = context->GetPhone(-1, feat->pause_context);
  // check for NULL value
  if (node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // extract value from XML
    phonename = node.attribute("val").value();
    // check and append value
    okay = cex->AppendValue(*feat, okay, phonename, buffer);
  }
  // return error status
  return okay;
}

// current phone name
bool CexFuncStringPhone(const TxpCexspec* cex,
                    const TxpCexspecFeat* feat,
                    const TxpCexspecContext* context,
                    std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* phonename;
  // get node from correct context
  node = context->GetPhone(0, feat->pause_context);
  // check for NULL value
  if (node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // extract value from XML
    phonename = node.attribute("val").value();
    // check and append value
    okay = cex->AppendValue(*feat, okay, phonename, buffer);
  }
  // return error status
  return okay;
}

// next phone name
bool CexFuncStringForwardPhone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* phonename;
  // get node from correct context
  node = context->GetPhone(1, feat->pause_context);
  // check for NULL value
  if (node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // extract value from XML
    phonename = node.attribute("val").value();
    // check and append value
    okay = cex->AppendValue(*feat, okay, phonename, buffer);
  }
  // return error status
  return okay;
}

// next next phone name
bool CexFuncStringForwardForwardPhone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* phonename;
  // get node from correct context
  node = context->GetPhone(2, feat->pause_context);
  // check for NULL value
  if (node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // extract value from XML
    phonename = node.attribute("val").value();
    // check and append value
    okay = cex->AppendValue(*feat, okay, phonename, buffer);
  }
  // return error status
  return okay;
}

// Segment location from front
bool CexFuncIntSegmentLocationFromFront(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node syllable_node;
  pugi::xml_node phone_node;
  int current_phone_id;

  phone_node = context->GetPhone(0, feat->pause_context);

  // Subtracting 1 here as the ids start at 1 in the xml,
  // but we want them to effectively start at 0.
  current_phone_id = atoi(phone_node.attribute("phonid").value()) - 1;

  // check and append value
  okay = cex->AppendValue(*feat, okay, current_phone_id, buffer);

  return okay;
}

// Segment location from back
bool CexFuncIntSegmentLocationFromBack(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node syllable_node;
  pugi::xml_node phone_node;
  int current_phone_id;
  int num_phones;

  syllable_node = context->GetSyllable(0, feat->pause_context);
  phone_node = context->GetPhone(0, feat->pause_context);

  num_phones = atoi(syllable_node.attribute("nophons").value());

  current_phone_id = atoi(phone_node.attribute("phonid").value());

  int dist_from_back = num_phones - current_phone_id;

  // check and append value
  okay = cex->AppendValue(*feat, okay, dist_from_back, buffer);

  return okay;
}

// Left syllable num phones
bool CexFuncIntBackwardSyllableNumPhones(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_phones;

  node = context->GetSyllable(-1, feat->pause_context);

  num_phones = atoi(node.attribute("nophons").value());

  // check and append value
  okay = cex->AppendValue(*feat, okay, num_phones, buffer);

  return okay;
}

// Current syllable num phones
bool CexFuncIntSyllableNumPhones(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_phones;

  node = context->GetSyllable(0, feat->pause_context);

  num_phones = atoi(node.attribute("nophons").value());

  // check and append value
  okay = cex->AppendValue(*feat, okay, num_phones, buffer);

  return okay;
}

// Right syllable num phones
bool CexFuncIntForwardSyllableNumPhones(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_phones;

  node = context->GetSyllable(1, feat->pause_context);

  num_phones = atoi(node.attribute("nophons").value());

  // check and append value
  okay = cex->AppendValue(*feat, okay, num_phones, buffer);

  return okay;
}

// Left syllable stress
bool CexFuncIntBackwardSyllableStress(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int stressval;
  // Get parent syllable node.
  node = context->GetSyllable(-1, feat->pause_context);
  // Check for NULL value
  if (node.empty()) {
    stressval = 0;
  } else {
    // extract value from XML
    stressval = atoi(node.attribute("stress").value());
  }
  // check and append value
  okay = cex->AppendValue(*feat, okay, stressval, buffer);
  // return error status
  return okay;
}

// Current syllable stress
bool CexFuncIntSyllableStress(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int stressval;
  // Get parent syllable node.
  node = context->GetSyllable(0, feat->pause_context);
  // Check for NULL value
  if (node.empty()) {
    stressval = 0;
  } else {
    // extract value from XML
    stressval = atoi(node.attribute("stress").value());
  }
  // check and append value
  okay = cex->AppendValue(*feat, okay, stressval, buffer);
  // return error status
  return okay;
}

// Right syllable stress
bool CexFuncIntForwardSyllableStress(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int stressval;
  // Get parent syllable node.
  node = context->GetSyllable(1, feat->pause_context);
  // Check for NULL value
  if (node.empty()) {
    stressval = 0;
  } else {
    // extract value from XML
    stressval = atoi(node.attribute("stress").value());
  }
  // check and append value
  okay = cex->AppendValue(*feat, okay, stressval, buffer);
  // return error status
  return okay;
}

// Left token pos tag
bool CexFuncStringBackwardWordPosTag(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* pos_tag;
  // Get parent utterance.
  node = context->GetWord(-1, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("pos");
  if (attribute.empty()) {
    pos_tag = "PAU";
  } else {
    pos_tag = attribute.value();
  }
  // check and append value
  okay = cex->AppendValue(*feat, okay, pos_tag, buffer);
  // return error status
  return okay;
}

// Current token pos tag
bool CexFuncStringWordPosTag(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* pos_tag;
  // Get parent utterance.
  node = context->GetWord(0, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("pos");
  if (attribute.empty()) {
    pos_tag = "PAU";
  } else {
    pos_tag = attribute.value();
  }
  // check and append value
  okay = cex->AppendValue(*feat, okay, pos_tag, buffer);
  // return error status
  return okay;
}

// Right token pos tag
bool CexFuncStringForwardWordPosTag(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  const char* pos_tag;
  // Get parent utterance.
  node = context->GetWord(1, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("pos");
  if (attribute.empty()) {
    pos_tag = "PAU";
  } else {
    pos_tag = attribute.value();
  }
  // check and append value
  okay = cex->AppendValue(*feat, okay, pos_tag, buffer);
  // return error status
  return okay;
}

// Left word num. syllables
bool CexFuncIntBackwardWordNumSyls(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_syllables;
  // Get parent utterance.
  node = context->GetWord(-1, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("nosyl");
  if (attribute.empty()) {
    num_syllables = 0;
  } else {
    num_syllables = atoi(attribute.value());
  }
  // check and append value
    okay = cex->AppendValue(*feat, okay, num_syllables, buffer);
  // return error status
  return okay;
}

// Current word num. syllables
bool CexFuncIntWordNumSyls(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_syllables;
  // Get parent utterance.
  node = context->GetWord(0, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("nosyl");
  if (attribute.empty()) {
    num_syllables = 0;
  } else {
    num_syllables = atoi(attribute.value());
  }
  // check and append value
    okay = cex->AppendValue(*feat, okay, num_syllables, buffer);
  // return error status
  return okay;
}

// Right word num. syllables
bool CexFuncIntForwardWordNumSyls(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_syllables;
  // Get parent utterance.
  node = context->GetWord(1, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("nosyl");
  if (attribute.empty()) {
    num_syllables = 0;
  } else {
    num_syllables = atoi(attribute.value());
  }
  // check and append value
    okay = cex->AppendValue(*feat, okay, num_syllables, buffer);
  // return error status
  return okay;
}

// Current phrase num. words
bool CexFuncIntPhraseNumWords(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int num_words;
  // Get parent utterance.
  node = context->GetSpurt(0, feat->pause_context);
  // Check for NULL value
  pugi::xml_attribute attribute = node.attribute("no_wrds");
  if (attribute.empty()) {
    num_words = 0;
  } else {
    num_words = atoi(attribute.value());
  }
  // check and append value
    okay = cex->AppendValue(*feat, okay, num_words, buffer);
  // return error status
  return okay;
}

// Current phrase ToBI end tone
bool CexFuncStringPhraseTobiEndTone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) {
  bool okay = true;
  pugi::xml_node node;
  int break_type;
  // Get parent spurt, then look down to see if we have a break.
  node = context->GetSpurt(0, feat->pause_context);
  // Iterate through spurt's children to find break.
  pugi::xml_node break_node;

  break_node = node.child("break");

  if (break_node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // Get break type.
    break_type = atoi(break_node.attribute("type").value());

    // Convert the type to a name.
    const char* break_name;

    if (break_type == 3) {
      break_name = "LH";
      // check and append value
      okay = cex->AppendValue(*feat, okay, break_name, buffer);
    } else if (break_type == 4) {
      break_name = "LL";
      // check and append value
      okay = cex->AppendValue(*feat, okay, break_name, buffer);
    } else {
      cex->AppendNull(*feat, buffer);
    }
  }
  // return error status
  return okay;
}

// Kaldi style current phone name. Kaldi includes _B/I/E/S for word position
// equating to begining, intermediate, end and standalone.
// Also as per idlak voice build we include the syllabic stress of the nucleus
// i.e dh_B ax0_E k_B ae1_I t_E etc. etc.
// This utility function unpacks this information for a given non-silent
// phone node
static bool KaldiPhone(const TxpCexspec* cex,
                       const TxpCexspecFeat* feat,
                       const TxpCexspecContext* context,
                       std::string* buffer,
                       int32 phon_pos) {
  bool okay = true;
  pugi::xml_node node;
  pugi::xml_node sylnode;
  pugi::xml_node tknode;
  std::string phonename;
  // get node from correct context
  node = context->GetPhone(phon_pos, feat->pause_context);
  // check for NULL value
  if (node.empty()) {
    cex->AppendNull(*feat, buffer);
  } else {
    // extract phone value from XML
    phonename = node.attribute("val").value();
    // get the syllable and token the phone is in
    sylnode = context->GetContextUp(node, "syl");
    tknode = context->GetContextUp(sylnode, "tk");
    // if a nucleus extract stress
    if (!strcmp("nucleus", node.attribute("type").value())) {
      phonename += sylnode.attribute("stress").value();
    }
    // work out word context
    // standalone phone or a pause (has no nosyls attribute)
    if (tknode.attribute("nosyl").empty() ||
        (!strcmp("1", tknode.attribute("nosyl").value()) &&
         !strcmp("1", sylnode.attribute("nophons").value())))
      phonename += "_S";
    else if (!strcmp("1", sylnode.attribute("sylid").value()) &&
             !strcmp("1", node.attribute("phonid").value()))
      phonename += "_B";
    else if (!strcmp(sylnode.attribute("sylid").value(),
                tknode.attribute("nosyl").value()) &&
        !strcmp(node.attribute("phonid").value(),
                sylnode.attribute("nophons").value()))
      phonename += "_E";
    else
      phonename += "_I";
    okay = cex->AppendValue(*feat, okay, phonename.c_str(), buffer);
  }
  // return error status
  return okay;
}

bool CexFuncStringBackwardBackwardPhoneKaldi(const TxpCexspec* cex,
                                             const TxpCexspecFeat* feat,
                                             const TxpCexspecContext* context,
                                             std::string* buffer) {
  return KaldiPhone(cex, feat, context, buffer, -2);
}

bool CexFuncStringBackwardPhoneKaldi(const TxpCexspec* cex,
                                     const TxpCexspecFeat* feat,
                                     const TxpCexspecContext* context,
                                     std::string* buffer) {
  return KaldiPhone(cex, feat, context, buffer, -1);
}

bool CexFuncStringPhoneKaldi(const TxpCexspec* cex,
                             const TxpCexspecFeat* feat,
                             const TxpCexspecContext* context,
                             std::string* buffer) {
  return KaldiPhone(cex, feat, context, buffer, 0);
}

bool CexFuncStringForwardPhoneKaldi(const TxpCexspec* cex,
                                    const TxpCexspecFeat* feat,
                                    const TxpCexspecContext* context,
                                    std::string* buffer) {
  return KaldiPhone(cex, feat, context, buffer, 1);
}

bool CexFuncStringForwardForwardPhoneKaldi(const TxpCexspec* cex,
                                    const TxpCexspecFeat* feat,
                                    const TxpCexspecContext* context,
                                    std::string* buffer) {
  return KaldiPhone(cex, feat, context, buffer, 2);
}

// position of the current syllable in the current word (forward)
bool CexFuncIntCurSyllablePosInWord(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node sylnode = context->GetSyllable(0, feat->pause_context);

  pugi::xml_attribute attribute = sylnode.attribute("sylid");
  int sylid = 0;
  if (!attribute.empty()) {
    sylid = atoi(attribute.value());
  }

  okay = cex->AppendValue(*feat, okay, sylid, buffer);
  return okay;           
}

// position of the current syllable in the current word ((backward)
bool CexFuncIntCurSyllablePosInWordBackward(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node wordnode = context->GetWord(0, feat->pause_context);
  pugi::xml_attribute attribute =  wordnode.attribute("nosyl");
  int sylno = 0;
  if (!attribute.empty()) {
    sylno = atoi(attribute.value());
  }

  int sylid = 0; 
  if (sylno > 0)
  {
    pugi::xml_node sylnode = context->GetSyllable(0, feat->pause_context);
    attribute = sylnode.attribute("sylid");
      
    if (!attribute.empty()) {
      sylid = atoi(attribute.value());
    }
    
    if (sylno > sylid)
    {
      sylid = sylno - sylid;
    }
    else
    {
      sylid = sylno;
    }
  }
  
  okay = cex->AppendValue(*feat, okay, sylid, buffer);
  return okay;          
}

bool CexFuncIntCurSyllablePosInPhrase(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node sylnode = context->GetSyllable(0, feat->pause_context);
  pugi::xml_node wordnode = context->GetWord(0, feat->pause_context);
  
  int wordid = -(atoi(wordnode.attribute("wordid").value()) - 1);
  int synum = 0;
  while (wordid < 0)
  {
    pugi::xml_node wordnode = context->GetWord(wordid, feat->pause_context);
    synum += atoi(wordnode.attribute("nosyl").value());
    wordid++;
  }

  synum  += atoi(sylnode.attribute("sylid").value());
  okay = cex->AppendValue(*feat, okay, synum, buffer);
  return okay;           
}

bool CexFuncIntCurSyllablePosInPhraseBackward(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node sylnode = context->GetSyllable(0, feat->pause_context);
  pugi::xml_node spurnode = context->GetSpurt(0, feat->pause_context);
  pugi::xml_node wordnode = context->GetWord(0, feat->pause_context);
  
  int wordno = atoi(spurnode.attribute("no_wrds").value());
  int wordcount = wordno - atoi(wordnode.attribute("wordid").value()) + 1;
  int synum = 0;
  int cur = 1;
  while (cur < wordcount)
  {
    pugi::xml_node wordnode = context->GetWord(cur, feat->pause_context);
    synum += atoi(wordnode.attribute("nosyl").value());
    cur++;
  }

  int sylno = atoi(wordnode.attribute("nosyl").value());
  synum  += sylno - atoi(sylnode.attribute("sylid").value());
  okay = cex->AppendValue(*feat, okay, synum, buffer);
  return okay;           
}
bool isVowel(std::string phone)
{
  static std::string vowel_list[] = {"aa","ae", "ah", "ao", "ah", "ay","eh", "er", "ey", "ih", "iy", "ow", "oy", "uh", "uw"};

  for (int i = 0; i < 15; i++)
  {
    if (vowel_list[i] == phone)
    {
      return true;
    }
  }
  return false;
}
bool CexFuncStringCurSyllableVowel(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node phonenode = context->GetPhone(0, feat->pause_context);
  pugi::xml_node sylnode = context->GetSyllable(0, feat->pause_context);
  std::string phone = phonenode.attribute("val").value();
  bool found = false;
  if (!isVowel(phone))
  {
    int phoneno = atoi(sylnode.attribute("nophons").value());
    int cur = -(atoi(phonenode.attribute("phonid").value()) - 1);
    while (cur < 0)
    {
      phonenode = context->GetPhone(cur, feat->pause_context);
      std::string phonec = phonenode.attribute("val").value();
      if (isVowel(phonec))
      {
        phone = phonec;
        found = true;
        break;
      }
      cur++;
    }

    if (!found)
    {
        int count  = phoneno - atoi(sylnode.attribute("phonid").value()) + 1;
        cur = 1;
        while (cur < count)
        {
          phonenode = context->GetPhone(cur, feat->pause_context);
          std::string phonec = phonenode.attribute("val").value();
          if (isVowel(phonec))
          {
            phone = phonec;
            found = true;
              break;
          }
          cur++;
        }
    }
  }
  else
  {
    found = true;
  }
  if (found)
  {
    okay = cex->AppendValue(*feat, okay, phone.c_str(), buffer);
  }
  else
  {
    okay = cex->AppendValue(*feat, okay, "X", buffer);
  }
  return okay;           
}

int GetTone(pugi::xml_node *node)
{
  int tone = 0;
  if (!node->empty())
  {
    pugi::xml_attribute attribute = node->attribute("tone");
    if (!attribute.empty()) {
      tone = atoi(attribute.value());
    }
  }
  return tone;
}

bool CexFuncIntCurPhoneTone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node phonenode = context->GetPhone(0, feat->pause_context);
  int tone = GetTone(&phonenode);
  okay = cex->AppendValue(*feat, okay, tone, buffer);
  return okay;
}

bool CexFuncIntBackwardPhoneTone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node phonenode = context->GetPhone(-1, feat->pause_context);
  int tone = GetTone(&phonenode);
  okay = cex->AppendValue(*feat, okay, tone, buffer);
  return okay;
}

bool CexFuncIntForwardPhoneTone(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  pugi::xml_node phonenode = context->GetPhone(1, feat->pause_context);
  int tone = GetTone(&phonenode);
  okay = cex->AppendValue(*feat, okay, tone, buffer);
  return okay;
}

bool CexFuncIntNotImp(const TxpCexspec* cex,
                     const TxpCexspecFeat* feat,
                     const TxpCexspecContext* context,
                     std::string* buffer) 
{
  bool okay = true;
  okay = cex->AppendValue(*feat, okay, 0, buffer);
  return okay;
}
}  // namespace kaldi
