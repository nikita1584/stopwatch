#define finish  2
#define clk     3
#define rst_n   4
#define d0      5
#define start   6
#define start_2 7
#define vcc_1   12
#define vcc_0   11
#define gnd_1   10
#define gnd_0   9

bool digit_0[8];
bool digit_1[8];
bool digit_2[8];
bool digit_3[8];
bool digit_4[8];
const bool number_0[] = {0,0,1,1,1,1,1,1}; //{1, 1, 1, 1, 1, 1, 0, 0};
const bool number_1[] = {0,0,0,0,0,1,1,0}; //{0, 1, 1, 0, 0, 0, 0, 0};
const bool number_2[] = {0,1,0,1,1,0,1,1}; //{1, 1, 0, 1, 1, 0, 1, 0};
const bool number_3[] = {0,1,0,0,1,1,1,1}; //{1, 1, 1, 1, 0, 0, 1, 0};
const bool number_4[] = {0,1,1,0,0,1,1,0}; //{0, 1, 1, 0, 0, 1, 1, 0};
const bool number_5[] = {0,1,1,0,1,1,0,1}; //{1, 0, 1, 1, 0, 1, 1, 0};
const bool number_6[] = {0,1,1,1,1,1,0,1}; //{1, 0, 1, 1, 1, 1, 1, 0};
const bool number_7[] = {0,0,0,0,0,1,1,1}; //{1, 1, 1, 0, 0, 0, 0, 0};
const bool number_8[] = {0,1,1,1,1,1,1,1}; //{1, 1, 1, 1, 1, 1, 1, 0};
const bool number_9[] = {0,1,1,0,1,1,1,1}; //{1, 1, 1, 1, 0, 1, 1, 0};
const bool number_flash[] = {1, 0, 1, 1, 1, 1, 1, 1};
const bool number_black[] = {0, 1, 0, 0, 0, 0, 0, 0};

int i;
int sec_10;
int seconds;
int sec_dec;
int minutes;
int min_dec;
bool even;
bool first_start;
volatile bool stop_counter;
void write_digits();
void reset_regs();

void setup() {
  Serial.begin(9600);
  i = 0;
  seconds = 0;
  minutes = 0;
  even = false;
  stop_counter = false;
  first_start = true;

  pinMode(clk, OUTPUT);
  pinMode(rst_n, OUTPUT);
  pinMode(d0, OUTPUT);
  pinMode(start, INPUT);
  pinMode(start_2, INPUT);
  pinMode(finish, INPUT);
  pinMode(vcc_1, OUTPUT);
  pinMode(vcc_0, OUTPUT);
  pinMode(gnd_1, OUTPUT);
  pinMode(gnd_0, OUTPUT);
  digitalWrite(clk, HIGH);
  digitalWrite(vcc_1, HIGH);
  digitalWrite(vcc_0, HIGH);
  digitalWrite(gnd_1, LOW);
  digitalWrite(gnd_0, LOW);

  digitalWrite(rst_n, HIGH);
  delay(10);
  digitalWrite(rst_n, LOW);
  delay(10);
  digitalWrite(rst_n, HIGH);
  delay(10);

  reset_regs();
  write_digits();
 
  while((digitalRead(start) == LOW) | (digitalRead(start_2) == LOW))
    delay(100);

  attachInterrupt(digitalPinToInterrupt(finish), stop_chrono, CHANGE);
}

void loop() {

  //if(digitalRead(start) == HIGH)
  //while(true)
  if(first_start & ((digitalRead(start) == LOW) | (digitalRead(start_2) == LOW)))
  {
    while((digitalRead(start) == LOW) | (digitalRead(start) == LOW))
      delay(1);
    stop_counter = false;

    for(minutes = 0; (minutes < 100) && !stop_counter; minutes++)
    {
      min_dec = minutes / 10;
      switch(min_dec){
        case 0:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_0[i];
          break;
        case 1:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_1[i];
          break;
        case 2:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_2[i];
          break;
        case 3:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_3[i];
          break;
        case 4:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_4[i];
          break;
        case 5:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_5[i];
          break;
        case 6:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_6[i];
          break;
        case 7:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_7[i];
          break;
        case 8:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_8[i];
          break;
        case 9:
          for(i = 0; i < 8; i++)
            digit_4[i] = number_9[i];
        break;
      }

      switch(minutes % 10){
        case 0:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_0[i];
          break;
        case 1:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_1[i];
          break;
        case 2:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_2[i];
          break;
        case 3:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_3[i];
          break;
        case 4:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_4[i];
          break;
        case 5:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_5[i];
          break;
        case 6:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_6[i];
          break;
        case 7:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_7[i];
          break;
        case 8:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_8[i];
          break;
        case 9:
          for(i = 0; i < 8; i++)
            digit_3[i] = number_9[i];
          break;
      }

      for(seconds = 0; (seconds < 60) && !stop_counter; seconds++)
      {
        sec_dec = seconds / 10;
        switch(sec_dec){
          case 0:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_0[i];
            break;
          case 1:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_1[i];
            break;
          case 2:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_2[i];
            break;
          case 3:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_3[i];
            break;
          case 4:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_4[i];
            break;
          case 5:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_5[i];
            break;
          case 6:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_6[i];
            break;
          case 7:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_7[i];
            break;
          case 8:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_8[i];
            break;
          case 9:
            for(i = 0; i < 8; i++)
              digit_2[i] = number_9[i];
            break;
        }

        switch(seconds%10){
          case 0:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_0[i];
            break;
          case 1:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_1[i];
            break;
          case 2:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_2[i];
            break;
          case 3:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_3[i];
            break;
          case 4:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_4[i];
            break;
          case 5:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_5[i];
            break;
          case 6:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_6[i];
            break;
          case 7:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_7[i];
            break;
          case 8:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_8[i];
            break;
          case 9:
            for(i = 0; i < 8; i++)
              digit_1[i] = number_9[i];
            break;
        }

        for(sec_10 = 0; (sec_10 < 10) && !stop_counter; sec_10++)
        {
          switch(sec_10){
            case 0:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_0[i];
              break;
            case 1:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_1[i];
              break;
            case 2:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_2[i];
              break;
            case 3:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_3[i];
              break;
            case 4:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_4[i];
              break;
            case 5:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_5[i];
              break;
            case 6:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_6[i];
              break;
            case 7:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_7[i];
              break;
            case 8:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_8[i];
              break;
            case 9:
              for(i = 0; i < 8; i++)
                digit_0[i] = number_9[i];
              break;
          }

          write_digits();
          //delay(999);
          delay(99);
          if(((digitalRead(start) == LOW) | (digitalRead(start_2) == LOW)) & !first_start)
          {
            minutes = 0;
            seconds = 0;
            sec_10 = 0;
            first_start = true;
            reset_regs();
            write_digits();
            while((digitalRead(start) == LOW) | (digitalRead(start_2) == LOW))
              delay(100);
            return;
          }
          first_start = false;
        }
      }
    }
  }
}

void stop_chrono(){
  static unsigned long millis_prev;
  if(millis()-100 > millis_prev)
    delayMicroseconds(1);
  millis_prev = millis();
  stop_counter = true;
  while((digitalRead(start) == HIGH) & (digitalRead(start_2) == HIGH))//high
    delay(50);
  if((digitalRead(start) == LOW) | (digitalRead(start_2) == LOW))
  {
    minutes = 0;
    seconds = 0;
    sec_10 = 0;
    stop_counter = false;
    reset_regs();
    write_digits();
    while((digitalRead(start) == LOW) | (digitalRead(start_2) == LOW))
      delay(100);
    first_start = true;
    return;
  }
}

void write_digits(){
  //writing 4 digit
  //delayMicroseconds
  for(i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
      if(digit_4[i])
        digitalWrite(d0, HIGH);
      else
        digitalWrite(d0, LOW);
    delayMicroseconds(1);
    digitalWrite(clk, HIGH);
    delayMicroseconds(1);
  }

  //writing 3 digit
  for(i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
    if(digit_3[i])
      digitalWrite(d0, HIGH);
    else
      digitalWrite(d0, LOW);
    delayMicroseconds(1);
    digitalWrite(clk, HIGH);
    delayMicroseconds(1);
  }

  //writing 2 digit
  for(i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
    if(digit_2[i])
      digitalWrite(d0, HIGH);
    else
      digitalWrite(d0, LOW);
    delayMicroseconds(1);
    digitalWrite(clk, HIGH);
    delayMicroseconds(1);
  }

  //writing 1 digit
  for(i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
    if(digit_1[i])
      digitalWrite(d0, HIGH);
    else
      digitalWrite(d0, LOW);
    delayMicroseconds(1);
    digitalWrite(clk, HIGH);
    delayMicroseconds(1);
  }

  //writing 0 digit
  for(i = 0; i < 8; i++)
  {
    digitalWrite(clk, LOW);
    if(digit_0[i])
      digitalWrite(d0, HIGH);
    else
      digitalWrite(d0, LOW);
    delayMicroseconds(1);
    digitalWrite(clk, HIGH);
    delayMicroseconds(1);
  }

  delayMicroseconds(250);//920
}

void reset_regs(){
  for(i = 0; i < 8; i++){
    digit_0[i] = number_0[i];
    digit_1[i] = number_0[i];
    digit_2[i] = number_0[i];
    digit_3[i] = number_0[i];
    digit_4[i] = number_0[i];
  }
  return;
}
