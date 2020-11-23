

/// periph.clavier.queue
/*
void ajouter_dans_queue(input_event inp, input_event *queue)
{ unsigned char index = 0;
  while (index < 12)
  { if (!(queue[index].input) || queue[index].input == inp.input)
    { queue[index] = inp;
      break; }
    index += 1; }}

void enlever_de_queue(input_event inp, input_event *queue)
{ unsigned char index = 0;
  while (index < 12 && queue[index].input)
  {  if (queue[index].input == inp.input - 9)
    { //printf("QUEUE::%lu, INP::%lu\n", queue[index].input, inp.input);
      break; }
    index += 1; }
  index += 1;
  while (index < 12 && queue[index - 1].input)
  { queue[index - 1] = queue[index];
    index += 1; }}
  
input_event *chercher_dans_queue(Inputs pattern, input_event *queue)
{ unsigned char index = 0;
  while (index < 12 && queue[index].input)
  { if (queue[index].input == pattern)
    { return (&(queue[index])); }
    index += 1; }
  return ((void*)0); }
*/

