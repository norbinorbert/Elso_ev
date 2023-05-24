#ifndef QUEUE_H
#define QUEUE_H

class queue {
	struct node {
		int adat;
		node* elozo;
		node* kovetkezo;
	};
	node* fej;
	node* vege;

public:
	queue();
	~queue();
	void push(int);
	void pop();
	int front();
	bool IsEmpty();
	void ListQueue();
};

#endif // !QUEUE_H
