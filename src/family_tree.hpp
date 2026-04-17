#pragma once

#include <iostream>
#include <string>

#include "node/node.h"

struct Member {
	int id = 0;
	std::string name;
	std::string last_name;
	char gender = 'H';
	int age = 0;
	int id_boss = -1;
	bool is_dead = false;
	bool in_jail = false;
	bool was_boss = false;
	bool is_boss = false;
};

inline std::ostream& operator<<(std::ostream& os, const Member& member) {
	os << "id=" << member.id
	   << ", name=" << member.name
	   << ", last_name=" << member.last_name
	   << ", gender=" << member.gender
	   << ", age=" << member.age
	   << ", id_boss=";

	if (member.id_boss < 0) {
		os << "NULL";
	} else {
		os << member.id_boss;
	}

	os << ", is_dead=" << (member.is_dead ? 1 : 0)
	   << ", in_jail=" << (member.in_jail ? 1 : 0)
	   << ", was_boss=" << (member.was_boss ? 1 : 0)
	   << ", is_boss=" << (member.is_boss ? 1 : 0);
	return os;
}

class FamilyTree {
public:
	FamilyTree() = default;
	~FamilyTree() {
		destroy(root_);
	}

	bool insert(const Member& member) {
		if (contains(root_, member.id)) {
			return false;
		}

		if (root_ == nullptr) {
			if (member.id_boss != -1) {
				return false;
			}
			root_ = new Node<Member>(member, nullptr, nullptr);
			return true;
		}

		Node<Member>* boss = findById(root_, member.id_boss);
		if (boss == nullptr) {
			return false;
		}

		if (boss->getLeft() == nullptr) {
			boss->setLeft(new Node<Member>(member, nullptr, nullptr));
			return true;
		}

		if (boss->getRight() == nullptr) {
			boss->setRight(new Node<Member>(member, nullptr, nullptr));
			return true;
		}

		return false;
	}

	void printAll() const {
		printPreOrder(root_, false);
	}

	void printLiving() const {
		printPreOrder(root_, true);
	}

	bool getCurrentBoss(Member& out_member) const {
		Node<Member>* boss = findCurrentBoss(root_);
		if (boss == nullptr) {
			return false;
		}

		out_member = boss->getData();
		return true;
	}

	bool applyBossRules() {
		Node<Member>* current_boss = findCurrentBoss(root_);
		if (current_boss == nullptr) {
			Node<Member>* candidate = findFirstEligibleInSubtree(root_, false, true);
			if (candidate == nullptr) {
				candidate = findFirstEligibleInSubtree(root_, true, true);
			}
			if (candidate == nullptr) {
				return false;
			}
			setAsCurrentBoss(candidate);
			return true;
		}

		const Member boss_data = current_boss->getData();
		if (canLead(boss_data, false)) {
			return true;
		}

		Node<Member>* candidate = findReplacementForBoss(current_boss, false);
		if (candidate == nullptr) {
			candidate = findReplacementForBoss(current_boss, true);
		}
		if (candidate == nullptr) {
			return false;
		}

		setAsCurrentBoss(candidate);
		return true;
	}

private:
	Node<Member>* root_ = nullptr;

	static bool canLead(const Member& member, bool allowJailed) {
		if (member.is_dead) {
			return false;
		}
		if (member.age > 70) {
			return false;
		}
		if (!allowJailed && member.in_jail) {
			return false;
		}
		return true;
	}

	static void destroy(Node<Member>* node) {
		if (node == nullptr) {
			return;
		}

		destroy(node->getLeft());
		destroy(node->getRight());
		delete node;
	}

	static Node<Member>* findById(Node<Member>* node, int id) {
		if (node == nullptr) {
			return nullptr;
		}

		if (node->getData().id == id) {
			return node;
		}

		if (Node<Member>* left = findById(node->getLeft(), id)) {
			return left;
		}

		return findById(node->getRight(), id);
	}

	static bool contains(Node<Member>* node, int id) {
		return findById(node, id) != nullptr;
	}

	static Node<Member>* findParentById(Node<Member>* node, int child_id) {
		if (node == nullptr) {
			return nullptr;
		}

		Node<Member>* left = node->getLeft();
		if (left != nullptr && left->getData().id == child_id) {
			return node;
		}

		Node<Member>* right = node->getRight();
		if (right != nullptr && right->getData().id == child_id) {
			return node;
		}

		if (Node<Member>* parent = findParentById(left, child_id)) {
			return parent;
		}

		return findParentById(right, child_id);
	}

	static Node<Member>* findCurrentBoss(Node<Member>* node) {
		if (node == nullptr) {
			return nullptr;
		}

		if (node->getData().is_boss) {
			return node;
		}

		if (Node<Member>* left = findCurrentBoss(node->getLeft())) {
			return left;
		}

		return findCurrentBoss(node->getRight());
	}

	static Node<Member>* findFirstEligibleInSubtree(Node<Member>* node, bool allowJailed, bool includeNode) {
		if (node == nullptr) {
			return nullptr;
		}

		if (includeNode && canLead(node->getData(), allowJailed)) {
			return node;
		}

		if (Node<Member>* left = findFirstEligibleInSubtree(node->getLeft(), allowJailed, true)) {
			return left;
		}

		return findFirstEligibleInSubtree(node->getRight(), allowJailed, true);
	}

	Node<Member>* findReplacementForBoss(Node<Member>* current_boss, bool allowJailed) {
		Node<Member>* candidate = findFirstEligibleInSubtree(current_boss, allowJailed, false);
		if (candidate != nullptr) {
			return candidate;
		}

		Node<Member>* pivot = current_boss;
		while (pivot != nullptr) {
			Node<Member>* parent = findParentById(root_, pivot->getData().id);
			if (parent == nullptr) {
				break;
			}

			Node<Member>* sibling = parent->getLeft() == pivot ? parent->getRight() : parent->getLeft();
			candidate = findFirstEligibleInSubtree(sibling, allowJailed, true);
			if (candidate != nullptr) {
				return candidate;
			}

			pivot = parent;
		}

		return findFirstEligibleInSubtree(root_, allowJailed, true);
	}

	void clearBossFlags(Node<Member>* node) {
		if (node == nullptr) {
			return;
		}

		Member data = node->getData();
		data.is_boss = false;
		node->setData(data);

		clearBossFlags(node->getLeft());
		clearBossFlags(node->getRight());
	}

	void setAsCurrentBoss(Node<Member>* new_boss) {
		Node<Member>* previous = findCurrentBoss(root_);
		if (previous != nullptr) {
			Member old_data = previous->getData();
			old_data.is_boss = false;
			old_data.was_boss = true;
			previous->setData(old_data);
		}

		clearBossFlags(root_);

		Member new_data = new_boss->getData();
		new_data.is_boss = true;
		new_data.was_boss = true;
		new_boss->setData(new_data);
	}

	static void printPreOrder(Node<Member>* node, bool onlyLiving) {
		if (node == nullptr) {
			return;
		}

		const Member& member = node->getData();
		if (!onlyLiving || !member.is_dead) {
			node->print();
		}

		printPreOrder(node->getLeft(), onlyLiving);
		printPreOrder(node->getRight(), onlyLiving);
	}
};