#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* ================= GLOBALS ================= */

GtkWidget *display;
GtkWidget *history_view;
GtkTextBuffer *history_buffer;

char expression[512] = "";
double memory_value = 0;

/* ================= EXPRESSION ENGINE ================= */

typedef struct { double items[512]; int top; } NumStack;
typedef struct { char items[512]; int top; } OpStack;

void push_num(NumStack *s,double v){ s->items[++s->top]=v; }
double pop_num(NumStack *s){ return s->items[s->top--]; }

void push_op(OpStack *s,char v){ s->items[++s->top]=v; }
char pop_op(OpStack *s){ return s->items[s->top--]; }
char peek_op(OpStack *s){ return s->items[s->top]; }

int prec(char op){
    if(op=='+'||op=='-') return 1;
    if(op=='*'||op=='/') return 2;
    return 0;
}

double apply(double a,double b,char op){
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return b!=0?a/b:0;
    }
    return 0;
}

double evaluate(const char *expr){
    NumStack nums={.top=-1};
    OpStack ops={.top=-1};

    for(int i=0;expr[i];i++){
        if(isspace(expr[i])) continue;

        if(isdigit(expr[i])||expr[i]=='.'){
            double val;
            sscanf(&expr[i],"%lf",&val);
            push_num(&nums,val);
            while(isdigit(expr[i])||expr[i]=='.') i++;
            i--;
        }
        else{
            while(ops.top!=-1 &&
                  prec(peek_op(&ops))>=prec(expr[i])){
                double b=pop_num(&nums);
                double a=pop_num(&nums);
                push_num(&nums,apply(a,b,pop_op(&ops)));
            }
            push_op(&ops,expr[i]);
        }
    }

    while(ops.top!=-1){
        double b=pop_num(&nums);
        double a=pop_num(&nums);
        push_num(&nums,apply(a,b,pop_op(&ops)));
    }

    return pop_num(&nums);
}

/* ================= HISTORY ================= */

void add_history(const char *expr,double result){
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(history_buffer,&end);

    char line[256];
    sprintf(line,"%s = %g\n",expr,result);

    gtk_text_buffer_insert(history_buffer,&end,line,-1);
}

/* ================= UI FUNCTIONS ================= */

void append(GtkWidget *w,gpointer data){
    strcat(expression,(char*)data);
    gtk_entry_set_text(GTK_ENTRY(display),expression);
}

void clear_all(GtkWidget *w,gpointer d){
    strcpy(expression,"");
    gtk_entry_set_text(GTK_ENTRY(display),"");
}

void calculate(GtkWidget *w,gpointer d){
    double result=evaluate(expression);

    add_history(expression,result);

    char buf[100];
    sprintf(buf,"%g",result);

    gtk_entry_set_text(GTK_ENTRY(display),buf);
    strcpy(expression,buf);
}

/* ================= MEMORY ================= */

void memory_add(GtkWidget *w, gpointer d){
    const char *text = gtk_entry_get_text(GTK_ENTRY(display));
    memory_value += atof(text);
}

void memory_sub(GtkWidget *w, gpointer d){
    const char *text = gtk_entry_get_text(GTK_ENTRY(display));
    memory_value -= atof(text);
}

void memory_recall(GtkWidget *w, gpointer d){
    char buf[100];
    sprintf(buf,"%g",memory_value);
    gtk_entry_set_text(GTK_ENTRY(display),buf);
    strcpy(expression,buf);
}

void memory_clear(GtkWidget *w, gpointer d){
    memory_value = 0;
}

/* ================= KEYBOARD SUPPORT ================= */

gboolean key_press(GtkWidget *w,GdkEventKey *event,gpointer d){
    char c=event->keyval;

    if((c>='0'&&c<='9')||c=='.'||c=='+'||c=='-'||c=='*'||c=='/'){
        char s[2]={c,'\0'};
        strcat(expression,s);
        gtk_entry_set_text(GTK_ENTRY(display),expression);
    }
    if(c==GDK_KEY_Return)
        calculate(NULL,NULL);
    if(c==GDK_KEY_BackSpace){
        int len=strlen(expression);
        if(len>0){
            expression[len-1]='\0';
            gtk_entry_set_text(GTK_ENTRY(display),expression);
        }
    }
    return FALSE;
}

/* ================= MAIN ================= */

int main(int argc,char *argv[]){
    gtk_init(&argc,&argv);

    GtkWidget *win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win),"Pro Calculator");
    gtk_window_set_default_size(GTK_WINDOW(win),450,600);
    g_signal_connect(win,"destroy",
                     G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(win,"key-press-event",
                     G_CALLBACK(key_press),NULL);

    GtkWidget *main_box=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    gtk_container_add(GTK_CONTAINER(win),main_box);

    display=gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(display),FALSE);
    gtk_box_pack_start(GTK_BOX(main_box),display,FALSE,FALSE,5);

    GtkWidget *grid=gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid),5);
    gtk_grid_set_column_spacing(GTK_GRID(grid),5);
    gtk_box_pack_start(GTK_BOX(main_box),grid,TRUE,TRUE,5);

    const char *buttons[]={
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0",".","=","+"
    };

    int row=0,col=0;
    for(int i=0;i<16;i++){
        GtkWidget *btn=gtk_button_new_with_label(buttons[i]);
        if(strcmp(buttons[i],"=")==0)
            g_signal_connect(btn,"clicked",G_CALLBACK(calculate),NULL);
        else
            g_signal_connect(btn,"clicked",G_CALLBACK(append),
                             (gpointer)buttons[i]);
        gtk_grid_attach(GTK_GRID(grid),btn,col,row,1,1);
        col++;
        if(col==4){col=0;row++;}
    }

    /* Memory buttons */
    GtkWidget *mem_box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_pack_start(GTK_BOX(main_box),mem_box,FALSE,FALSE,5);

    GtkWidget *madd=gtk_button_new_with_label("M+");
    GtkWidget *msub=gtk_button_new_with_label("M-");
    GtkWidget *mrec=gtk_button_new_with_label("MR");
    GtkWidget *mclr=gtk_button_new_with_label("MC");

    g_signal_connect(madd,"clicked",G_CALLBACK(memory_add),NULL);
    g_signal_connect(msub,"clicked",G_CALLBACK(memory_sub),NULL);
    g_signal_connect(mrec,"clicked",G_CALLBACK(memory_recall),NULL);
    g_signal_connect(mclr,"clicked",G_CALLBACK(memory_clear),NULL);

    gtk_box_pack_start(GTK_BOX(mem_box),madd,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(mem_box),msub,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(mem_box),mrec,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(mem_box),mclr,TRUE,TRUE,5);

    /* History panel */
    history_view=gtk_text_view_new();
    history_buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(history_view));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(history_view),FALSE);
    gtk_widget_set_size_request(history_view,-1,150);
    gtk_box_pack_start(GTK_BOX(main_box),history_view,TRUE,TRUE,5);

    /* DARK THEME CSS */
    GtkCssProvider *provider=gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "* { background:#121212; color:white; font-size:18px; }"
        "button { background:#1f1f1f; border-radius:10px; }"
        "entry { background:#1e1e1e; }",
        -1,NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
